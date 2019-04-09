#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

/* declare your struct for a person here */
typedef struct person {
  char* name;
  int age;
} person;

static void insert(person* people[], char *name, int age, int *nextinsert)
{
  people[*nextinsert] = malloc(sizeof(person));
  /* put name and age into the next free place in the array parameter here */
  people[*nextinsert]->name = name;
  people[*nextinsert]->age = age;
  /* modify nextfreeplace here */
  (*nextinsert)++;
}

int main(int argc, char **argv)
{
  /* declare the people array here */
  person *people[HOW_MANY];
  int i;
  int nextinsert = 0;
  for (i = 0; i < HOW_MANY; i++)
  {
    insert (people, names[i], ages[i], &nextinsert);
  }

  /* print the people array here*/
  for (i = 0; i < HOW_MANY; i++) {
    printf("%d: %s is %d\n", i, people[i]->name, people[i]->age);
  }

  for (i = 0; i < HOW_MANY; i++) {
    free(people[i]);
  }

  return 0;
}
