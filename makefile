lst: lst.o
	g++ -o lst lst.o

lst.o: lst.c
	g++ -c lst.c

clean:
	rm *.o lst