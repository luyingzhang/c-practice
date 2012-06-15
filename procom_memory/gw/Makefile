INCDIR  = ../include
INCLUDE = -I./ -I$(INCDIR) -I/usr/include 
LIB      = -lutil -lfisc -ltcp 
LDFLAGS  = -L/usr/lib  -L../lib

CCFLAG  = -g $(INCLUDE)

all:	fisc_gw fep_gw
	
fisc_gw: fisc_gw.o
	cc -o $@ $@.o $(LDFLAGS) $(LIB)
	mv $@ ../bin
	
fep_gw: fep_gw.o
	cc -o $@ $@.o $(LDFLAGS) $(LIB)
	mv $@ ../bin

.c.o:
	cc -c $(CCFLAG) $<

clean:
	rm -f *.o  
