CFLAGS += -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs

CFLAGS += -O2
CFLAGS += -std=c11  

CC = cc

shelf: shelf.o cmd.o io.o
	$(CC) -o shelf shelf.o cmd.o io.o

shelf.o:
	$(CC) $(CFLAGS) -c shelf.c

cmd.o:
	$(CC) $(CFLAGS) -c cmd.c

io.o:
	$(CC) $(CFLAGS) -c io.c

clean:
	rm -f shelf *.o *.h.gch
