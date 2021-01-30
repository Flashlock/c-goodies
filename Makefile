output: main.o goodies.o linked-list.o hashtable.o
	gcc main.o goodies.o linked-list.o hashtable.o -o output

main.o: main.c
	gcc -c main.c

goodies.o: goodies.c goodies.h
	gcc -c goodies.c

linked-list.o: ./data-structures/linked-list.c ./data-structures/linked-list.h
	gcc -c ./data-structures/linked-list.c

hashtable.o: ./data-structures/hashtable.c ./data-structures/hashtable.o
	gcc -c ./data-structures/hashtable.c

clean:
	rm *.o output

run:
	./output