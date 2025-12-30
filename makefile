CC = g++ -O3 -Wall -Werror -ansi -pedantic --std=c++17
FLAGS = -g -c

SOURCEDIR  = sources
BUILDDIR   = obj
BINDIR     = bin
ARCHIVE    = sortie.zip
CREATE_DIR = mkdir $(BUILDDIR) $(BINDIR)
PROG=manage_prg
TARGET_ARCHIVE=sources/*.cpp header/*.hpp  makefile
MSG_CLEAN=:Suppresion du programme executable $(PROG) et du fichier archive $(ARCHIVE)
MSG_BUILD_ZIP=Generation du fichier archive $(ARCHIVE)
MSG_CLEAN_O_FILE:=Suppresion des fichiers $(BUILDDIR)/.o

SOURCES    = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS    = $(patsubst $(SOURCEDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

CLEAN      =:
TROUVE     =: NON

help:
	@echo ' '
	@echo ' '
	@echo  Possible targets:
	@echo ' '
	@echo     make                   - print contain this section
	@echo     make clean             - delete bin and obj directories
	@echo     make mrproper          - delete bin, obj directories and zip file contain all code project if exists
	@echo     make dir               - create bin and obj directories
	@echo     make zip               - create zip $(ARCHIVE) file contain  sources/*.hpp, header/*.cpp and makefile
	@echo     make binary            - create all obj/*.o files from all sources/*.cpp files and binary bin/$(PROG) file
	@echo ' '
	@echo  Informations project
	@echo ' '
	@echo     sources files          - sources directory contain all sources/*.cpp files
	@echo     header files           - header directory contain all header/*.hpp files
	@echo ' '
	@echo ' '
	@echo  Binary file name
	@echo      $(PROG)
	@echo ' '
	@echo ' '

OSFLAG 				:=
OS_DETAILS          :=
ifeq ($(OS),Windows_NT)
	OSFLAG := WIN
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OS_DETAILS:=WIN_AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OS_DETAILS:=WIN_X86
	endif
else
	OSFLAG := $(shell uname -s | tr A-Z a-z)
	OS_DETAILS := $(OSFLAG)
endif

ifeq ($(OSFLAG), WIN)
    COMPIL:=Compilation sous windows
    DELETE:=del $(ARCHIVE)
    ZIP:=tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE)
    CLEAN = rmdir /q /s $(BUILDDIR) $(BINDIR)
    TROUVE:=OUI
    MSG_BUILD_END=Fin build des fichiers $(BUILDDIR)/.o et generation du fichier executable $(BINDIR)/$(PROG).exe
endif

ifeq ($(OSFLAG), linux)
	COMPIL:=Compilation sous Linux
	DELETE:=rm $(ARCHIVE)
	ZIP:=tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE)
	CLEAN:=rm -rf $(BUILDDIR) $(BINDIR) $(ARCHIVE)
	MSG_BUILD_END=Fin build des fichiers $(BUILDDIR)/.o et generation du fichier executable $(BINDIR)/$(PROG)
endif

ifeq ($(OSFLAG), darwin)
	COMPIL:=Compilation sous MacOs
	DELETE:=rm $(ARCHIVE)
	ZIP:=tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE)
	CLEAN:=rm -rf $(BUILDDIR) $(BINDIR) $(ARCHIVE)
	MSG_BUILD_END=Fin build des fichiers $(BUILDDIR)/.o et generation du fichier executable $(BINDIR)/$(PROG)
endif

ifeq ($(OSFLAG), WIN)
	CLEANER=rmdir /s /q $(BUILDDIR) $(BINDIR)

else
	CLEANER=rm -rf $(BUILDDIR) $(BINDIR)
endif

infos:
	@echo $(COMPIL)
	@echo $(MSG_BUILD_END)

binary:	dir $(BINDIR)/$(PROG)

dir:
	$(CLEANER)
	$(CREATE_DIR)

create_dir:
	$(CREATE_DIR)

$(BINDIR)/$(PROG): $(OBJECTS)
	@echo $(COMPIL)
	@echo $(MSG_BUILD_END)
	$(CC) $^ -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(FLAGS) $< -o $@

clean:
	$(DELETE)
	$(CLEANER)
	$(CREATE_DIR)

mrproper:
	$(CLEAN)
	$(CREATE_DIR)

zip:
	@echo $(MSG_BUILD_ZIP)
	$(ZIP)