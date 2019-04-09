#include <stdio.h>
#include <stdlib.h>

enum staffStudent{staff, student, neither};
typedef union moreFacts {
  char *programme_name;
  char *room_number;
} moreFacts;
/* declare your struct for a person here */
typedef struct person {
  char* name;
  int age;
  enum staffStudent staff_or_student;
  moreFacts extraInfo;
  struct person *pNext;
  struct person *pPrev;
} person;


person *insert_start(person *people, char *nextName, int nextAge
                   , int nextType, char *nextFacts);
person *insert_end(person *people, char *nextName, int nextAge
                   , int nextType, char *nextFacts);
person *insert_sorted(person *people, char *nextName, int nextAge
                    , int (*compare_people)(person*, person*)
                    , int nextType, char *nextFacts);
