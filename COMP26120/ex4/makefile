CC=gcc
CFLAGS=-g -std=c99 -Wall
#LDFLAGS=-lm

test: arrays
	./arrays

part2:
	$(CC) $(CFLAGS) slists.c test.c -o test
	./test
	./test insert_start
	./test insert_end
	./test insert_sorted
	./test insert_sorted age
	./test insert_sorted name
part2d:
	$(CC) $(CFLAGS) dlists.c test.c -DDOUBLE -o test2d
	./test2d
	./test2d insert_start
	./test2d insert_end
	./test2d insert_sorted
	./test2d insert_sorted age
	./test2d insert_sorted name
