CC=gcc
CFLAGS=-Wall -O2
LFLAGS=
EXTRA_LIBS=
AUX_CFLAGS=-DAU
PROGS=decode encode
DONE=echo
RM=rm
RMFLAGS=-f

.c.o:
	$(CC) -c $(CFLAGS) $(AUX_CFLAGS) $<

all: $(PROGS)
	$(DONE)

decode: decode.o qlookup.o b3.o misc.o ileave.o scramble.o top456.o
	$(CC) $(LFLAGS) $(AUX_LFLAGS) -o decode \
	decode.o qlookup.o b3.o misc.o ileave.o scramble.o top456.o \
	$(EXTRA_LIBS)

encode: encode.o qlookup.o b3.o ileave.o scramble.o misc.o top456.o best.o
	$(CC) $(LFLAGS) $(AUX_LFLAGS) -o encode \
	encode.o qlookup.o b3.o ileave.o scramble.o misc.o top456.o best.o
	$(EXTRA_LIBS)

b3.o:		b3.c		b3.h
best.o:		best.c		best.h
decode.o:	decode.c	vcrplus.h misc.h ileave.h scramble.h b3.h \
				top456.h
encode.o:	encode.c	b3.h vcrplus.h ileave.h scramble.h misc.h \
				top456.h best.h
ileave.o:	ileave.c	vcrplus.h ileave.h
misc.o:		misc.c		misc.h
qlookup.o:	qlookup.c	vcrplus.h
scramble.o:	scramble.c	scramble.h
top456.o:	top456.c

#
# ~STD TARGETS~
#
#
install:
	echo no 'install' support
#
sysinstall:
	echo no 'sysinstall' support
#
archive:
	zip lingcode.zip GENERAL Makefile database.txt dispdeco \
	encode decode *.h *.c
#
touch:
	echo no 'touch' support
#
cleanprogs:
	-$(RM) $(RMFLAGS) $(PROGS)
#
cleanobjs:
	-$(RM) $(RMFLAGS) *.o
#
cleanbase:
	echo no 'cleanbase' support
#
realclean: cleanobjs cleanprogs
	echo 'realclean' done
#
clean: cleanobjs cleanprogs
	-$(RM) $(RMFLAGS) core
#
checkin:
	echo no 'checkin' support
#
checkout:
	echo no 'checkout' support
#
print:
	echo no 'print' support
#
# ~END STD TARGETS~
#
