CC=clang
 
# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=SOURCES
HEADDIR=SOURCES
LIBDIR=OBJS
BINDIR=OBJS
RAPDIR=RAPPORT
EXEC=delaunay
 
# Les différentes options de compilations, soyons strictes !
CFLAGS= -I$(HEADDIR) -g -Wall -pedantic -Os
# Les différents FrameWorks et bibliothèques pour le linkage
GL_INCLUDE    = -I/usr/include/GL
GL_LIBDIR    = -L. -L/usr/X11R6/lib
GL_LIBRARIES = -lglut -lGL -lm -lGLU -lXmu -lXext -lXi -lX11

# Add objectiveC library for MacOSX.
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Apple")),)
	GL_INCLUDE    = -I/usr/X11R6/include
	GL_LIBRARIES += -lobjc
	BROWSER = dillo
	OS = "osx"
endif
# Nothing to be done for Linux :o)
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Linux")),)
	OS = "linux"
	BROWSER = mozilla
endif
 
# Où trouver les différents sources *.c qu'il faudra compiler pour créer les objets correspondants
SRC= $(wildcard $(SRCDIR)/*.c)
OBJ= $(SRC:$(SRCDIR)/%.c=$(LIBDIR)/%.o)
 
all: $(EXEC)
	./$(EXEC) 
 
#Création de l'exécutable
$(EXEC): $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(GL_LIBDIR) $(GL_LIBRARIES)
	
# Création des différents *.o à partir des *.c
$(LIBDIR)/%.o: $(SRCDIR)/%.c $(HEADDIR)/%.h 
	$(CC) $(GL_INCLUDE) -o $@ -c $< $(CFLAGS)

$(LIBDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(GL_INCLUDE) -o $@ -c $< $(CFLAGS)
 
# Nettoyage des objets 
clean:
	rm -rf $(LIBDIR)/*.o
 
# Nettoyage complet (.o + executable)
veryclean:
	rm -rf $(BINDIR)/*

# Nettoyage total (.o, executable, doc et rapport)
cleanAll: veryclean
	rm -rf DOCS/*
	rm -rf $(RAPDIR)/*.aux $(RAPDIR)/*.toc $(RAPDIR)/*.log
	rm -rf $(RAPDIR)/*.pdf

doc: 
	doxygen $(SRCDIR)/Doxyfile

rapport:
	pdflatex $(RAPDIR)/*.tex 
	mv *.pdf *.aux *.log *.toc $(RAPDIR)/

lireRapport:
	acroread $(RAPDIR)/*.pdf&


