# $Id: Makefile.in 105 2012-01-22 22:13:17Z gyunaev $
CC = gcc
CFLAGS = -Wall -DIN_BUILDING_LIBIRC -g -O2 -O3 -DENABLE_THREADS -D_REENTRANT
AR=ar cr
RANLIB=ranlib
INCLUDES=-I../include
DESTDIR=

OBJS = libircclient.o

all:	static

static:	libircclient.a
shared: libircclient.so
shared_mingw: libircclient.dll

install: lib
	-mkdir -p $(DESTDIR)/usr/local/include
	-mkdir -p $(DESTDIR)/usr/local/lib
	cp ../include/libircclient.h $(DESTDIR)/usr/local/include/libircclient.h
	cp ../include/libirc_errors.h $(DESTDIR)/usr/local/include/libirc_errors.h
	cp ../include/libirc_events.h  $(DESTDIR)/usr/local/include/libirc_events.h 
	cp ../include/libirc_options.h  $(DESTDIR)/usr/local/include/libirc_options.h 
	cp ../include/libirc_rfcnumeric.h  $(DESTDIR)/usr/local/include/libirc_rfcnumeric.h 
	cp libircclient.so $(DESTDIR)/usr/local/lib/
	cp libircclient.a $(DESTDIR)/usr/local/lib/

libircclient.so: libircclient.o
	$(CC) -shared -s -o libircclient.so libircclient.o  -lnsl

libircclient.dll: libircclient.o
	$(CC) -shared -s -o libircclient.dll -Wl,-out-implib,libircclient.lib libircclient.o libircclient.def -lkernel32 -lwsock32  -lnsl

libircclient.a: libircclient.o
	$(AR) libircclient.a libircclient.o
	$(RANLIB) libircclient.a

clean:
	rm -f libircclient.a libircclient.o

distclean: clean
	-rm -f Makefile

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
