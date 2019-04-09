#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlists.h"

//change type to person pointer; returns pointer to new head
person *insert_start(person *people, char *nextName, int nextAge, int nextType, char* info)
{
  person *newPerson = malloc(sizeof(person));//create new space for new person
  //check if successful malloc
  if (!newPerson) {
    printf("ERROR! Unsuccessful malloc.\n");
    exit(1);
  } else {
    //set data for new person
    //allocating nextName length + 1 because of termination character
    newPerson->name = malloc((strlen(nextName) + 1)*sizeof(char));
    strcpy(newPerson->name, nextName);
    newPerson->age = nextAge;
    newPerson->staff_or_student = nextType;
    if (nextType == staff) {
      newPerson->extraInfo.room_number = malloc((strlen(info) + 1)*sizeof(char));
      strcpy(newPerson->extraInfo.room_number, info);
    } else if (nextType == student) {
      newPerson->extraInfo.programme_name = malloc((strlen(info) + 1)*sizeof(char));
      strcpy(newPerson->extraInfo.programme_name, info);
    }//if
    //set the new person's next link to point to the (start of) current list
    newPerson->pNext = people;
    if (people != NULL) {
      people->pPrev = newPerson;
    }
    newPerson->pPrev = NULL;
    //return head of new list
    people = newPerson;
    return people;
  }//if
}//insert_start

person *insert_end(person *people, char *nextName, int nextAge, int nextType, char* info)
{
  person *newPerson = malloc(sizeof(person));//create new space for new person
  //check if successful malloc
  if (!newPerson) {
    printf("ERROR! Unsuccessful malloc.\n");
    exit(1);
  } else {
    //set data for new person
    newPerson->name = malloc((strlen(nextName) + 1)*sizeof(char));
    strcpy(newPerson->name, nextName);
    newPerson->age = nextAge;
    newPerson->staff_or_student = nextType;
    if (nextType == staff) {
      newPerson->extraInfo.room_number = malloc((strlen(info) + 1)*sizeof(char));
      strcpy(newPerson->extraInfo.room_number, info);
    } else if (nextType == student) {
      newPerson->extraInfo.programme_name = malloc((strlen(info) + 1)*sizeof(char));
      strcpy(newPerson->extraInfo.programme_name, info);
    }//if
    //Initial next and prev pointers to null
    newPerson->pNext = NULL;
    //check if current list is empty, in which case...
    if (people == NULL) {
      newPerson->pPrev = NULL;
      return newPerson;
    } else {
      //...otherwise loop through to find the last item in list
      person *someBloke = people;
      while (someBloke->pNext != NULL) {
        someBloke = someBloke->pNext;
      }//while
      //set next link to point to new node
      someBloke->pNext = newPerson;
      newPerson->pPrev = someBloke;
      return people;
    }//if
  }//if
}//insert_end

person *insert_sorted(person *people, char *nextName, int nextAge
                     ,int (*compare_people)(person*, person*)
                     ,int nextType, char* info)
{
  person *newPerson = malloc(sizeof(person));//create new space for new person
  //check if successful malloc
  if (!newPerson) {
    printf("ERROR! Unsuccessful malloc.\n");
    exit(1);
  } else {
    //set data for new person
    newPerson->name = malloc((strlen(nextName) + 1)*sizeof(char));
    strcpy(newPerson->name, nextName);
    newPerson->age = nextAge;
    newPerson->staff_or_student = nextType;
    if (nextType == staff) {
      newPerson->extraInfo.room_number = malloc((strlen(info) + 1)*sizeof(char));
      strcpy(newPerson->extraInfo.room_number, info);
    } else if (nextType == student) {
      newPerson->extraInfo.programme_name = malloc((strlen(info) + 1)*sizeof(char));
      strcpy(newPerson->extraInfo.programme_name, info);
    }//if
    //check if current list is empty or newPerson < first item, in which case...
    if (people == NULL || compare_people(newPerson, people) < 0) {
      newPerson->pNext = people;
      //people->pPrev = newPerson;
      newPerson->pPrev = NULL;
      return newPerson;
    } else {
      //...otherwise loop through to find the last item that is < new person
      person *currentPerson = people;//start at head
      person *trailPerson = people;
      //while current person isn't last element AND currentPerson < newPerson
      while (currentPerson->pNext != NULL && compare_people(currentPerson, newPerson) <= 0) {
        trailPerson = currentPerson;
        currentPerson = currentPerson->pNext;
      }//while
      //If we happen to insert it at the end
      if (trailPerson->pNext == NULL) {
        trailPerson->pNext = newPerson;
        newPerson->pPrev = trailPerson;
        newPerson->pNext = NULL;
      } else {
        //If it's somewhere in the middle of the list...
        //set newPerson's next link to point to next item in list
        trailPerson->pNext = newPerson;
        newPerson->pPrev = trailPerson;
        newPerson->pNext = trailPerson->pNext;
        trailPerson->pNext->pPrev = newPerson;
      }
      return people;
    }//if
  }//if
}//insert_sorted
