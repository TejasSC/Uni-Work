#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#ifdef DOUBLE
  #include "dlists.h"
#else
  #include "slists.h"
#endif
#include "printing.h"

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
      people = insert_start(people, names[i], ages[i], person_type[i], info[i]);
    }//for
  } else if (argc == 2){
    if (strcmp(argv[1], "insert_start")==0) {
      for (i = 0; i < HOW_MANY; i++) {
        people = insert_start(people, names[i], ages[i], person_type[i], info[i]);
      }//for
    } else if (strcmp(argv[1], "insert_end")==0) {
      for (i = 0; i < HOW_MANY; i++) {
        people = insert_end(people, names[i], ages[i], person_type[i], info[i]);
      }//for
    } else if (strcmp(argv[1], "insert_sorted")==0) {
      for (i = 0; i < HOW_MANY; i++) {
        people = insert_sorted(people, names[i], ages[i], compare_people_by_name, person_type[i], info[i]);
      }//for
    } else {
      printf("Invalid argument supplied\n");
      exit(0);
    }//else
  } else if (argc == 3) {
    if (strcmp(argv[1], "insert_sorted")==0) {
      if (strcmp(argv[2], "name")==0) {
        for (i = 0; i < HOW_MANY; i++) {
          people = insert_sorted(people, names[i], ages[i], compare_people_by_name, person_type[i], info[i]);
        }//for
      } else if (strcmp(argv[2], "age")==0) {
        for (i = 0; i < HOW_MANY; i++) {
          people = insert_sorted(people, names[i], ages[i], compare_people_by_age, person_type[i], info[i]);
        }//for
      } else {
        printf("Invalid sorting type supplied\n");
        exit(0);
      }//else
    } else {
      printf("Invalid insertion type supplied\n");
      exit(0);
    }//else
  } else {
    printf("Wrong number of arguments supplied\n");
    exit(0);
  }//else

  person *someBloke = people;//references lost without auxiliary head pointer
  #ifdef DOUBLE
    for (i = 0; i < HOW_MANY - 1; i++) {
      someBloke = someBloke->pNext;//update so list actually traversable
    }
    for (i = 0; i < HOW_MANY; i++) {
      printData(someBloke);
      someBloke = someBloke->pPrev;
    }
  #else
    for (i = 0; i < HOW_MANY; i++) {
      printData(someBloke);
      someBloke = someBloke->pNext;//update so list actually traversable
    }
  #endif

  //Points to element behind head in LL
  for (i = 0; i < HOW_MANY; i++) {
    someBloke = people->pNext;//set someBloke to (i+1)th element
    if (people->staff_or_student == staff) {
      free(people->extraInfo.room_number);
    } else if (people->staff_or_student == student){
      free(people->extraInfo.programme_name);
    }
    free(people->name);
    free(people);//free the ith element
    people = someBloke;//assign people's new head to old value of someBloke
  }
  return 0;
}
