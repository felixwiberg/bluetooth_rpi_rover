IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lbluetooth -lncurses

_DEPS = 		#hej.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

all:client server

_OBJ = rfcomm-client.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

_OBJ = rfcomm-server.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 









#CC=gcc
#CFLAGS=-I.

#all: client server

#server: rfcomm-server.c
#	     $(CC) -o server rfcomm-server.c -lbluetooth

#client: rfcomm-client.c
#	     $(CC) -o client rfcomm-client.c -lbluetooth
