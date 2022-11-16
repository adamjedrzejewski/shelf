shelf: shelf.o commands.o fs.o io.o
	cc -o shelf shelf.o commands.o io.o fs.o

shelf.o:
	cc -c shelf.c constants.h types.h commands.h

commands.o:
	cc -c commands.c constants.h types.h

fs.o:
	cc -c fs.c types.h constants.h

io.o:
	cc -c io.c types.h constants.h

clean:
	rm -f shelf *.o *.h.gch
