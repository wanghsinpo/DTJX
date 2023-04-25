DMH_ROOT      = /opt/SPECS_FA/dmh

TCL_INCLUDE   = ${DMH_ROOT}/include

TCL_TK_SHARED_LIBS= ${DMH_ROOT}/lib

DMH_SHARED_LIB= ${DMH_ROOT}/lib/dmh84

SYSLIBS	      =	-ltcl8.4 -lm

LIBS	      = tec.o

CC	      = /usr/bin/gcc

CFLAGS	      = -g -c -fPIC -m32 \
		-DHISLIB -DHIS_MSGHUB \
		-I ${TCL_INCLUDE} -DTEC

LD	      = /usr/bin/gcc

LDFLAGS	      = -m32 \
		-L ${TCL_TK_SHARED_LIBS} \
		-L ${DMH_SHARED_LIB} \
		-L /opt/SPECS_FA/dmh/lib \
		-L /opt/SPECS_FA/dmh/lib/dmh84

DEST	      = .

EXTHDRS	      =

HDRS	      =

INSTALL	      = /usr/sbin/install

PROGRAM	      = tec

MAKEFILE      = Makefile

OBJS	      = rftag.o \
		serial.o

PRINT	      = pr

SHELL	      = /usr/bin/sh

SRCS	      = rftag.c \
		serial.c

SYSHDRS	      =

all:		$(PROGRAM)

$(PROGRAM):	$(OBJS) $(LIBS)
		@echo "Linking $(PROGRAM) ..."
		@$(LD) $(LDFLAGS) $(OBJS) $(LIBS) $(SYSLIBS) -o $(PROGRAM)
		@echo "done"

clean:;		@rm -f $(OBJS) core

clobber:;	@rm -f $(OBJS) $(PROGRAM) core tags

depend:;	@mkmf -f $(MAKEFILE) ROOT=$(ROOT)

echo:;		@echo $(HDRS) $(SRCS)

extract:;	@ar x $(DEST)/$(LIBRARY)

index:;		@ctags -wx $(HDRS) $(SRCS)

install:	$(PROGRAM)
		@echo Installing $(PROGRAM) in $(DEST)
		@-strip $(PROGRAM)
		@if [ $(DEST) != . ]; then \
		(rm -f $(DEST)/$(PROGRAM); $(INSTALL) -f $(DEST) $(PROGRAM)); fi

print:;		@$(PRINT) $(HDRS) $(SRCS)

tags:		$(HDRS) $(SRCS); @ctags $(HDRS) $(SRCS)

###
