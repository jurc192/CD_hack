# To so spremenljivke, ki jih lahko definiraš
CC = gcc
CFLAGS = -c -Wall

all: myprogram

myprogram: myprogram.o function1.o function2.o
	$(CC) -o myprogram myprogram.o function1.o function2.o

myprogram.o: myprogram.c
	$(CC) $(CFLAGS) myprogram.c

function1.o: function1.c
	$(CC) $(CFLAGS) function1.c

function2.o: function2.c
	$(CC) $(CFLAGS) function2.c

clean:
	rm -rf *o myprogram


# Makefile je file, ki ti skompajla program iz več različnih sourceou.
# To narediš z ukazom "make". Makefile mora bit tko poimenovan "Makefile"
# in v isti mapi kot sourci.
# All, clean ipd -> to so TARGET
# za dvopičjem so -> DEPENDENCY
# v drugi vrstici, s TABulatorjem -> COMMAND
# po defoltu se izvede prvi target, razen če napišeš npr. "make clean"

# PRVA VARIANTA ====
# all:
# 	gcc -o myprogram myprogram.c function1.c function2.c
# ==================


# DRUGA VARIANTA ====
# all: myprogram
#
# myprogram: myprogram.o function1.o function2.o
# 	gcc -o myprogram myprogram.o function1.o function2.o
#
# myprogram.o: myprogram.c
# 	gcc -c myprogram.c
#
# function1.o: function1.c
# 	gcc -c function1.c
#
# function2.o: function2.c
# 	gcc -c function2.c
#
# clean:
# 	rm -rf *o myprogram
# ==================
