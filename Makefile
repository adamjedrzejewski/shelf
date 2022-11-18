shelf: shelf.o commands.o io.o
	cc -o shelf shelf.o commands.o io.o

shelf.o:
	cc -c shelf.c

commands.o:
	cc -c commands.c

io.o:
	cc -c io.c

clean:
	rm -f shelf *.o *.h.gch
