
CC=gcc
CFLAGS= -std=c99 -W -Wall -O2
LDFLAGS= -lSDLmain -lSDL -lSDL_ttf
EXEC=picture
SRCDIR = src
BINDIR = bin
SRC= $(SRCDIR)/line_solving.c $(SRCDIR)/column_solving.c $(SRCDIR)/solver.c $(SRCDIR)/display.c $(SRCDIR)/main.c $(SRCDIR)/grid_loader.c $(SRCDIR)/picture_loader.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

picture: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(SRCDIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
