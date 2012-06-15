SRCS   = fisc_shm.c fisc_log.c fisc_str.c
OBJS   = ${SRCS:.c=.o}
CCFLAG  = -g -I../include
LIBDIR = ../lib
TARGET = $(LIBDIR)/libfisc.a

all:	$(TARGET)

$(TARGET): $(OBJS)
	ar rv $(TARGET) $(OBJS)

.c.o:
	cc -c $(CCFLAG) $<
	ar rv $(TARGET) $@
	
clean:
	rm -f $(OBJS) $(TARGET) 