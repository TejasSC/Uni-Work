CC=gcc
CFLAGS=-Wall -pedantic -g -std=c99
LDFLAGS=-Iinclude -lm -lgmp 

elGamal:
	$(CC) $(CFLAGS) elGamal.c  -o elGamal $(LDFLAGS)

dl:
	$(CC) $(CFLAGS) dl.c  -o dl $(LDFLAGS)

elGamalGMP:
	$(CC) $(CFLAGS) elGamalGMP.c  -o elGamalGMP $(LDFLAGS)

clean:
	rm -rf *o elGamal dl elGamalGMP
