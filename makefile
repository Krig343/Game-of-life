CC = gcc -g -Wall
OBJETS = main.o grille.o io.o jeu.o
EXEC = main
IFLAGS = -I headers
OPATH = objets/
CPATH = source/
HPATH = headers/

vpath %.h headers
vpath %.c source
vpath %.o objets
vpath main bin

$(EXEC) : $(OBJETS)
	$(CC) -o $@ $(OPATH)main.o $(OPATH)grille.o $(OPATH)io.o $(OPATH)jeu.o
	mv $@ bin/

main.o : main.c grille.h io.h jeu.h

grille.o : grille.c grille.h

io.o : io.c io.h grille.h jeu.h

jeu.o : jeu.c jeu.h grille.h

%.o :
	$(CC) -c $< $(IFLAGS)
	mv $@ $(OPATH)

dist :
	tar -cv --lzma Doxyfile makefile $(CPATH)* $(HPATH)* -f GoL_g_horny.tar.xz

clean :
	rm bin/* objets/*
