#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct
{ // hash-table entry
  Key_Type element; // only data is the key itself
  enum {empty, in_use, deleted} state;
} cell;

typedef unsigned int Table_size; // type for size-of or index-into hash table
int totalCollisions = 0;
int numInserts = 0;
struct table
{
  cell *cells; Table_size table_size; // cell cells [table_size];
  Table_size num_entries; // number of cells in_use
  double avgCollisions;
};

//initialize table to (table_size) empty cells
Table initialize_table (Table_size ts)
{
  Table hashTable = (Table) malloc(sizeof(struct table));
  check(hashTable);
  hashTable->table_size = ts;
  hashTable->cells = malloc(ts*sizeof(cell));
  //initialise each cell to empty state
  for (int i = 0; i < hashTable->table_size; i++) {
    hashTable->cells[i].state = empty;
    hashTable->cells[i].element = NULL;//don't have elements if they're empty
  }//for
  hashTable->num_entries = 0;//because it's empty
  hashTable->avgCollisions = 0.0;
  return hashTable;
}//initialize_table

int power(int x, int y){
  int i;
  for (i = 0; i < y; i++) {
    x = x * x;
  }//for
  return x;
}

//polynomial hashcode function
int hashCodeA(Key_Type str_kt) {
  int len = strlen(str_kt);
  int seed = 41;//constant whose powers go from (string length - 1) to 0
  int hash = 0;//value of hash function on a string
  for (int i = 0; i < len; i++) {
    hash = hash + (power(seed, (len-1)-i))*str_kt[i];//(constant^power) * char
  }//for
  return hash;
}//hashCodeA

//summative hashcode function, used in double hashing algorithms
int hashCodeB(Key_Type str_kt) {
  int len = strlen(str_kt);
  int hash = 0;//value of hash function on a string
  for (int i = 0; i < len; i++) {
    hash = hash + str_kt[i];//(constant^power) * char
  }//for
  return hash;
}//hashCodeB

//inserts new element into an empty cell
void putItIn(Table table, int hashIndex, Key_Type str_kt){
  table->cells[hashIndex].state = in_use;
  int len = strlen(str_kt);
  table->cells[hashIndex].element = malloc(sizeof(char)*(len+1));
  strcpy(table->cells[hashIndex].element, str_kt);
  table->num_entries++;
}//putItIn

void insertLP(Key_Type str_kt, Table table, int hashIndex) {
  //Collision handling with linear probing
  //Insert at positions A[(i+j) mod N], j = 1,2,3... until free space found
  while (table->cells[hashIndex].state != empty) {
    hashIndex++;
    hashIndex = hashIndex % (table->table_size);
    totalCollisions++;
  }//while
  if (table->cells[hashIndex].state == empty) {
    putItIn(table, hashIndex, str_kt);
  }//if
}//insertLP

void insertQP (Key_Type str_kt, Table table, int hashIndex) {
  //Collision handling with Quadratic probing
  //Insert at positions A[(i+j) mod N], j = 1,2,3... until free space found
  int j = 0;
  int tempHash = hashIndex;
  while (table->cells[hashIndex].state != empty) {
    hashIndex = tempHash + j*j;//Quadratic because j², not j
    hashIndex = hashIndex % (table->table_size);
    j++;
    totalCollisions++;
  }//while
  if (table->cells[tempHash].state == empty) {
    putItIn(table, tempHash, str_kt);
  }//if
}//insertQP

void insertDH (Key_Type str_kt, Table table, int hashIndex) {
  //Collision handling with double hashing
  //Insert at positions A[(i+j) mod N], j = 1,2,3... until free space found
  int j = 1;
  int secondHash = hashCodeB(str_kt)%(table->table_size);
  int tempHash = hashIndex;
  while (table->cells[tempHash].state != empty) {
    hashIndex = tempHash + j*secondHash;//Quadratic because j², not j
    hashIndex = hashIndex % (table->table_size);
    j++;
    totalCollisions++;
  }//while
  if (table->cells[tempHash].state == empty) {
    putItIn(table, tempHash, str_kt);
  }//if
}//insertQP

//inserts elements into the same table, or a tabel twice as big if it's full
Table insert (Key_Type str_kt, Table table)
{
  numInserts++;
  if ((table->num_entries) == (table->table_size)) {
    int newSize = table->table_size * 2;//double table size
    Table new_table = initialize_table(newSize);
    for (int i = 0; i < new_table->table_size; i++) {
      new_table->cells[i].state = table->cells[i].state;
      new_table->cells[i].element = table->cells[i].element;
    }//for
    //calculate h(k), the hash index
    int hashIndex = hashCodeA(str_kt)%(new_table->table_size);
    if (mode == 1) {
      insertLP(str_kt, new_table, hashIndex);//linear probing
    } else if (mode == 2) {
      insertQP(str_kt, new_table, hashIndex);//Quadratic probing
    } else if (mode == 3) {
      insertDH(str_kt, new_table, hashIndex);//double hashing
    }//if
    return new_table;
  } else {
    //calculate h(k), the hash index
    int hashIndex = hashCodeA(str_kt)%(table->table_size);
    if (mode == 1) {
      insertLP(str_kt, table, hashIndex);//linear probing
    } else if (mode == 2) {
      insertQP(str_kt, table, hashIndex);//Quadratic probing
    } else if (mode == 3) {
      insertDH(str_kt, table, hashIndex);//double hashing
    }//if
    return table;
  }//if
}//insert

Boolean find (Key_Type str_kt, Table table)
{
  Boolean found = FALSE;
  int i = 0;
  while (!found && i < table->table_size) {
    if (strcmp(table->cells[i].element, str_kt) == 0) {
      found = TRUE;//
    }//if
    i++;
  }//while
  return found;
}//find

void print_table (Table table)
{
  int c = 0;
  for (int i = 0; i < table->table_size; i++) {
    printf("%d, %d\n", i, table->cells[i].state);
    //only print it if the cell is used by something
    if (table->cells[i].state == in_use) {
      c++;
      printf("%d of %d entries: %s\n", c, table->num_entries, table->cells[i].element);
    }//if
  }//for
}//print_table

//free string keys first then clear whole table once all is emptied
void tidy(Table table){
  int i = 0;
  for (i = 0; i < table->table_size; i++) {
    //free it if it's occupied
    if (table->cells[i].state == in_use) {
      free(table->cells[i].element);
    }//if
  }//for
  free(table->cells);
}//tidy

void print_stats (Table table)
{
  //average number of collisions calculated by ratio of total collisions to total inserts
  printf("%d collisions in total\n", totalCollisions);
  table->avgCollisions = totalCollisions / (double) numInserts;
  printf("%.2f collisions on average\n", table->avgCollisions);
}//print_stats
