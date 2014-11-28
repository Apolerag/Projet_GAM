 
CC=clang
 
 
# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=SOURCES
HEADDIR=SOURCES
LIBDIR=OBJS
BINDIR=OBJS
 
 
# Les différentes options de compilations, soyons strictes !
CFLAGS= -I$(HEADDIR) -g -Wall -pedantic -Os
# Les différents FrameWorks et bibliothèques pour le linkage
GL_INCLUDE    = -I/usr/include/GL
GL_LIBDIR    = -L. -L/usr/X11R6/lib
GL_LIBRARIES = -lglut -lGL -lm -lGLU -lXmu -lXext -lXi -lX11


 
# L'exécutable
BIN=delaunay
 
# Où trouver les différents sources *.c qu'il faudra compiler pour créer les objets correspondants
SRC= $(wildcard $(SRCDIR)/*.c)
OBJ= $(SRC:$(SRCDIR)/%.c=$(LIBDIR)/%.o)

 
all: $(BIN)
 
#Création de l'exécutable
delaunay: $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(GL_LIBDIR) $(GL_LIBRARIES)
 
# Création des différents *.o à partir des *.c
$(LIBDIR)/%.o: $(SRCDIR)/%.c $(HEADDIR)/%.h 
	@echo "fzf"
	$(CC) $(GL_INCLUDE) -o $@ -c $< $(CFLAGS)

$(LIBDIR)/%.o: $(SRCDIR)/%.c
	@echo "fzf"
	$(CC) $(GL_INCLUDE) -o $@ -c $< $(CFLAGS)
 
# Nettoyage des objets 
clean:
	rm -rf $(LIBDIR)/*.o
 
# Nettoyage complet (.o + executable)
veryclean:
	rm -rf $(BINDIR)/*

# Nettoyage total (.o, executable, doc et rapport)
cleanAll::
	rm -rf OBJS/* DOCS/* $(EXEC)
	rm -rf RAPPORT/*.aux RAPPORT/*.toc RAPPORT/*.log
	rm -rf RAPPORT/*.pdf

doc: 
	doxygen SOURCES/main.dox

rapport:
	pdflatex RAPPORT/*.tex
	mv *.pdf *.aux *.log *.toc RAPPORT/