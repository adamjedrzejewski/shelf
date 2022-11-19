shelf: shelf.o cmd.o io.o
	cc -o shelf shelf.o cmd.o io.o

shelf.o:
	cc -c shelf.c

cmd.o:
	cc -c cmd.c

io.o:
	cc -c io.c

clean:
	rm -f shelf *.o *.h.gch
