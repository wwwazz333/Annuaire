CC = gcc -std=c99
EXEC = main

SRCDIR = src
SRC = $(wildcard src/*.c)
OBJDIR = obj
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

FLAGS = -Iinclude -g3 -Wall -Wextra

WINDOWS = no

all : $(EXEC)

release : 
	$(CC) $(SRCDIR)/*.c -Iinclude -O2 -o main

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(FLAGS) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

ifeq ($(WINDOWS), yes)
clean :
	del .\\$(OBJDIR)\\*.o
	del $(EXEC).exe	
else
clean : 
	rm -rf $(OBJDIR)/*.o 
	rm $(EXEC)
endif