CC=gcc
CFLAGS=-g -std=c99 -Wall
LDFLAGS=-lm

test2a:
		./part2a #no params
		./part2a "one argument"
		./part2a "largest arguement" "first" "in" "list"
		./part2a "end" "arguement" "biggest" "WOOOOOOOOOOOOOOOOO"
		./part2a "The" "biggest" "is" "right here" "in" "the" "middle"
		./part2a "two" "things" "have" "the" "same" "length"

test2b:
		./part2b && exit 1 || [ $$? -eq 1 ] #no parameters
		./part2b "-c" "123" "three" && exit 1 || [ $$? -eq 1 ] #should give exit code 1
		./part2b "not f or c" "1.2" && exit 2 || [ $$? -eq 2 ] #exit code 2??
		./part2b "-f" "3A" && exit 3 || [ $$? -eq 3 ] #exit code 3?? malformed number
		./part2b "-c" "-274.15" && exit 4 || [ $$? -eq 4 ] #exit code 4?? temp below abs. zero
		./part2b "-c" 40  #must output 104 farenheit
		./part2b "-f" 70.0  #must output 21.11 celsius
