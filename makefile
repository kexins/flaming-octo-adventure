all: bathroomSim

bathroomSim: bathroomSim.o bathroom.o
	gcc -g -Wall -pthread -lm bathroomSim.o bathroom.o -o bathroomSim

bathroomSim.o: bathroomSim.c bathroomSim.h bathroom.h
	gcc -g -Wall -c -pthread bathroomSim.c 

bathroom.o: bathroom.c bathroom.h
	gcc -g -Wall -c -pthread bathroom.c 

clean:
	rm -f *.o;
	rm -f bathroomSim

