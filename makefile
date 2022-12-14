CC = gcc -g -Wall
OBJETS = main.o grille.o io.o jeu.o
EXEC = main
IFLAGS = -I headers
OPATH = objets/
CPATH = source/
HPATH = headers/
IFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS = -lcairo -lm -lX11 -ljeu -L./lib/
MODE = GRAPHIQUE
ifeq ($(MODE),TEXTE)
$(MODE) = TEXTE
endif

vpath %.h headers
vpath %.c source
vpath %.o objets
vpath main bin

$(EXEC) : $(OBJETS)
	$(CC) -o $@ $(OPATH)main.o $(OPATH)grille.o $(OPATH)io.o $(OPATH)jeu.o $(LDFLAGS)
	mv $@ bin/

main.o : main.c grille.h io.h jeu.h

libjeu.a : $(OBJETS)
	mkdir -p lib/
	ar -crv libjeu.a $(OPATH)grille.o $(OPATH)io.o $(OPATH)jeu.o
	ranlib libjeu.a
	mv $@ lib/

grille.o : grille.c grille.h

io.o : io.c io.h grille.h jeu.h

jeu.o : jeu.c jeu.h grille.h

%.o :
	$(CC) -c $< $(IFLAGS) -D$(MODE)
	mv $@ $(OPATH)

dist :
	tar -cv --lzma Doxyfile makefile $(CPATH)* $(HPATH)* -f HornyGrégory-GoL-v1_1.tar.xz
	mv *.tar.xz archives/

docu :
	mkdir -p doc/
	doxygen

clean_doc :
	rm -rf doc

clean_lib :
	rm -rf lib

clean :
	rm bin/* objets/*