#include <stdio.h>
#include <stdlib.h>
#include "slists.h"

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
    newPerson->name = nextName;
    newPerson->age = nextAge;
    newPerson->staff_or_student = nextType;
    if (nextType == staff) {
      newPerson->extraInfo.room_number = info;
    } else if (nextType == student) {
      newPerson->extraInfo.programme_name = info;
    }//if
    //set the new person's next link to point to the (start of) current list
    newPerson->pNext = people;
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
    newPerson->name = nextName;
    newPerson->age = nextAge;
    newPerson->staff_or_student = nextType;
    if (nextType == staff) {
      newPerson->extraInfo.room_number = info;
    } else if (nextType == student) {
      newPerson->extraInfo.programme_name = info;
    }//if
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
    newPerson->name = nextName;
    newPerson->age = nextAge;
    newPerson->staff_or_student = nextType;
    if (nextType == staff) {
      newPerson->extraInfo.room_number = info;
    } else if (nextType == student) {
      newPerson->extraInfo.programme_name = info;
    }//if
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
