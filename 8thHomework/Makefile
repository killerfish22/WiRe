SRC=main.c mmio.c helper.c
OUTPUT=tr_solve
CC=gcc
CFLAGS=-O2 -g 
LIBS= -lblas -lgfortran -lm 
OBJ=${SRC:.c=.o}

$(OUTPUT): $(OBJ)
	$(CC) -o $(OUTPUT) $(CFLAGS) $(OBJ) $(LIBS) 

.SUFFIXES: .c .o
.c.o:
	$(CC) -c -o $@ $(CFLAGS) $<
clean:
	rm -f $(OBJ)
.PHONY: clean 


