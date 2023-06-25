#Manage cpp project by Makefile

CC = g++ -Wall -ansi -pedantic -std=c++0x

PROG=manage_prj
PROG_WIN=manage_prj.exe
ARCHIVE=sortie.zip
TARGET_ARCHIVE=sources/*.cpp header/*.hpp *.dat makefile

ifeq ($(OS), linux)
	DELETE=rm -rf $(PROG) $(ARCHIVE)
	ZIP=tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE)
	CLEAN=rm -rf sources/*.o
else
	DELETE=del $(ARCHIVE) $(PROG_WIN)
	CLEAN=del sources\*.o
endif

#Identifier tous les fichiers .c de mon programme
SRC = $(wildcard sources/*.cpp)

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
	$(CLEAN)

mrproper: clean
	@echo "Suppresion du programme executable \"$(PROG)\" et du fichier archive \"$(ARCHIVE)\" : "
	$(DELETE)

zip:
	@echo "Generation du fichier archive \"$(ARCHIVE)\" : "
	$(ZIP)
