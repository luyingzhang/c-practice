SRCS   = hexdec.c hexncpy.c  ntgetopt.c pack.c comm_xml.c comm_queue.c\
		 password.c toupper.c unpack.c str_byte_xor.c getsysdatetime.c getms.c
OBJS   = ${SRCS:.c=.o}
CCFLAG  = -g -I../include
LIBDIR = ../lib
TARGET = $(LIBDIR)/libutil.a

all:	$(TARGET)

$(TARGET): $(OBJS)
	ar rv $(TARGET) $(OBJS)

.c.o:
	cc -c $(CCFLAG) $<
	ar rv $(TARGET) $@
	
clean:
	rm -f $(OBJS) $(TARGET) 