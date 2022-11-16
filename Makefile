shelf: shelf.o
	cc -o shelf shelf.o

shelf.o:
	cc -c shelf.c constants.h

clean:
	rm shelf *.o *.h.gch
