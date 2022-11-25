CFLAGS += -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs

CFLAGS += -O2
CFLAGS += -std=c11  


shelf: shelf.o cmd.o io.o
	cc -o shelf shelf.o cmd.o io.o

shelf.o:
	cc $(CFLAGS) -c shelf.c

cmd.o:
	cc $(CFLAGS) -c cmd.c

io.o:
	cc $(CFLAGS) -c io.c

clean:
	rm -f shelf *.o *.h.gch
