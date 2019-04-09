#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

/* declare your struct for a person here */
typedef struct person {
  char* name;
  int age;
  struct person *pNext;
} person;

//change type to person pointer; returns pointer to new head
static person *insert_start(person *people, char *nextName, int nextAge)
{
  person *newPerson = malloc(sizeof(person));//create new space for new person
  //check if successful malloc
  if (!newPerson) {
    printf("ERROR! Unsuccessful malloc.\n");
    exit(0);
  } else {
    //set data for new person
    newPerson->name = nextName;
    newPerson->age = nextAge;
    //set the new person's next link to point to the (start of) current list
    newPerson->pNext = people;
    //return head of new list
    people = newPerson;
    return people;
  }//if
}//insert_start

static person *insert_end(person *people, char *nextName, int nextAge)
{
  person *newPerson = malloc(sizeof(person));//create new space for new person
  //check if successful malloc
  if (!newPerson) {
    printf("ERROR! Unsuccessful malloc.\n");
    exit(0);
  } else {
    //set data for new person
    newPerson->name = nextName;
    newPerson->age = nextAge;
    newPerson->pNext = NULL;
    //check if current list is empty, in which case...
    if (people == NULL) {
      return newPerson;
    } else {
      //...otherwise loop through to find the last item in list
      person *someBloke = people;
      while (someBloke->pNext != NULL) {
        someBloke = someBloke->pNext;
      }//while
      //set next link to point to new node
      someBloke->pNext = newPerson;
      return people;
    }//if
  }//if
}//insert_end

static person *insert_sorted(person *people, char *nextName, int nextAge,
                             int (*compare_people)(person*, person*))
{
  person *newPerson = malloc(sizeof(person));//create new space for new person
  //check if successful malloc
  if (!newPerson) {
    printf("ERROR! Unsuccessful malloc.\n");
    exit(0);
  } else {
    //set data for new person
    newPerson->name = nextName;
    newPerson->age = nextAge;
    //check if current list is empty or newPerson < first item, in which case...
    if (people == NULL || compare_people(newPerson, people) < 0) {
      newPerson->pNext = people;
      return newPerson;
    } else {
      //...otherwise loop through to find the last item that is < new person
      person *currentPerson = people;//start at head
      person *trailPerson = people;
      //while current person isn't last element AND currentPerson < newPerson
      while (currentPerson && compare_people(currentPerson, newPerson) <= 0) {
        trailPerson = currentPerson;
        currentPerson = currentPerson->pNext;
      }//while
      //set newPerson's next link to point to next item in list
      newPerson->pNext = currentPerson;
      trailPerson->pNext = newPerson;
      return people;
    }//if
  }//if
}//insert_sorted

int compare_people_by_name(person *blokeA, person *blokeB) {
  return strcmp(blokeA->name, blokeB->name);
}//compare_people
int compare_people_by_age(person *blokeA, person *blokeB) {
  return blokeA->age - blokeB->age;
}//compare_people

int main(int argc, char **argv)
{
  person *people = NULL;
  int i;
  if (argc == 1) {
    for (i = 0; i < HOW_MANY; i++) {
      people = insert_start(people, names[i], ages[i]);
    }//for
  } else if (argc == 2){
    if (strcmp(argv[1], "insert_start")==0) {
      for (i = 0; i < HOW_MANY; i++) {
        people = insert_start(people, names[i], ages[i]);
      }//for
    } else if (strcmp(argv[1], "insert_end")==0) {
      for (i = 0; i < HOW_MANY; i++) {
        people = insert_end(people, names[i], ages[i]);
      }//for
    } else if (strcmp(argv[1], "insert_sorted")==0) {
      for (i = 0; i < HOW_MANY; i++) {
        people = insert_sorted(people, names[i], ages[i], compare_people_by_name);
      }//for
    } else {
      printf("EXITCODE is not 0\n");
      exit(0);
    }//else
  } else if (argc == 3) {
    if (strcmp(argv[1], "insert_sorted")==0) {
      if (strcmp(argv[2], "name")==0) {
        for (i = 0; i < HOW_MANY; i++) {
          people = insert_sorted(people, names[i], ages[i], compare_people_by_name);
        }//for
      } else if (strcmp(argv[2], "age")==0) {
        for (i = 0; i < HOW_MANY; i++) {
          people = insert_sorted(people, names[i], ages[i], compare_people_by_age);
        }//for
      } else {
        printf("EXITCODE is not 0\n");
        exit(0);
      }//else
    } else {
      printf("EXITCODE is not 0\n");
      exit(0);
    }//else
  } else {
    printf("EXITCODE is not 0\n");
    exit(0);
  }//else

  person *someBloke = people;//references lost without auxiliary head pointer
  for (i = 0; i < HOW_MANY; i++) {
    printf("Name: %s, age: %d\n", someBloke->name, someBloke->age);
    someBloke = someBloke->pNext;//update so list actually traversable
  }
  //Points to element behind head in LL
  for (i = 0; i < HOW_MANY; i++) {
    someBloke = people->pNext;//set someBloke to (i+1)th element
    free(people);//free the ith element
    people = someBloke;//assign people's new head to old value of someBloke
  }
  return 0;
}
