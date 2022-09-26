#Manage cpp project by Makefile

OS=linux

ifeq ($(OS), linux)
	DELETE=rm
else
	DELETE=del
endif

CC = g++ -g -Wall -ansi -pedantic -std=c++20

PROG=manage_prj
ARCHIVE=sortie.zip
TARGET_ARCHIVE=*.cpp *.hpp Makefile

#Identifier tous les fichiers .c de mon programme
SRC = $(wildcard *.cpp)

#Créer une liste des fichiers .o liés aux fichiers .c
OBJ = $(SRC:.cpp=.o)

all: $(PROG)

$(PROG): $(OBJ)
	@echo "Fin build des fichiers .o et generation du fichier executable ==> \"$(PROG)\" : " 
	$(CC) -o $@  $^ 

%.o : %.c
	$(CC) -o $@ -c $< 

clean:
	@echo "Suppresion des fichiers .o : " 
	$(DELETE) -rf *.o

mrproper: clean
	@echo "Suppresion du programme executable \"$(PROG)\" et du fichier archive \"$(ARCHIVE)\" : " 
	$(DELETE) -rf $(PROG) $(ARCHIVE)

zip:
	@echo "Generation du fichier archive \"$(ARCHIVE)\" : " 
	tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE) 
