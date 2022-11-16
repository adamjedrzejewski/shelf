shelf: shelf.o
	cc -o shelf shelf.o commands.o

shelf.o: commands.o
	cc -c shelf.c constants.h types.h commands.h

commands.o:
	cc -c commands.c constants.h types.h

clean:
	rm -f shelf *.o *.h.gch
