OBJ = main.o procedure.o
LFLAGS = -pthread
CFLAGS = -ggdb -Wall -g -O1
RM = rm -f
HEADER = header.h
BIN = gestore
CC = gcc


all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(LFLAGS) $(CFLAGS)
	
main.o: main.c $(HEADER)
	$(CC) -c main.c $(CFLAGS)
	
procedure.o: procedure.c $(HEADER)
	$(CC) -c procedure.c $(CFLAGS) 

clean:
	$(RM) *.c~ *.h~ $(OBJ) $(BIN) 
