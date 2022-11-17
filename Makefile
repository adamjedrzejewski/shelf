shelf: shelf.o commands.o fs.o io.o
	cc -o shelf shelf.o commands.o io.o fs.o

shelf.o:
	cc -c shelf.c

commands.o:
	cc -c commands.c

fs.o:
	cc -c fs.c

io.o:
	cc -c io.c

clean:
	rm -f shelf *.o *.h.gch
