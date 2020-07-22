CC=gcc
 
# Les différents répertoires contenant respectivement les fichiers :*.c,*.h,*.o,l'exécutable
SRCDIR=src
HEADDIR=include
BINDIR=bin
 

CFLAGS= -I$(HEADDIR) -g -Wall 
GLLIBS = -lm
 
# L'exécutable
BIN=code
 
# trouver les différents sources *.c qu'il faudra compiler pour créer les objets correspondants
SRC= $(wildcard $(SRCDIR)/*.c)
OBJ= $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)
 
all: $(BIN)
 
#Création de l'exécutable
code: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(GLLIBS)
 
# Créaation des différents *.o Ã  partir des *.c
$(BINDIR)/%.o: $(SRCDIR)/%.c $(HEADDIR)/%.h 
	$(CC) -o $@ -c $< $(CFLAGS)
 
 
# Nettoyage des objets => Tout sera recompiler !
clean:
	rm $(BINDIR)/*.o
 
# Nettoyage complet => clean + effacement du l'exécutable
Clean: clean
	rm $(BINDIR)/*
	

