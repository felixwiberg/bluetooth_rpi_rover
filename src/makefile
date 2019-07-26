IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib
_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

all:client server servo reset

LIBS=-lbluetooth -lncurses
_OBJ = rfcomm-client.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
client: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

LIBS=-lbluetooth -lncurses
_OBJ = rfcomm-server.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

LIBS=-lbluetooth -lncurses -lwiringPi -lwiringPiDev -lpthread -lwiringPiPca9685
_OBJ = servo.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
servo: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

LIBS=-lbluetooth -lncurses -lwiringPi -lwiringPiDev -lpthread -lwiringPiPca9685
_OBJ = reset.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
reset: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)




.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
