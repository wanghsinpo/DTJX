SPECS_INCLUDE = /opt/SPECS/sys/include

SPECS_LIB     = /opt/SPECS/usr/lib

DMH_ROOT      = /opt/SPECS_FA/dmh

TCL_INCLUDE   = ${DMH_ROOT}/include

TCL_TK_SHARED_LIBS= ${DMH_ROOT}/lib

DMH_SHARED_LIB= ${DMH_ROOT}/lib/dmh84

SYSLIBS	      = -ltcl8.4

CC	      = /usr/bin/gcc

CFLAGS	      = -g -c -fPIC -m32 \
		-I ${TCL_INCLUDE} \
		-I ${SPECS_INCLUDE}\
		-Wno-implicit-function-declaration

LD	      = /usr/bin/gcc

LDFLAGS	      = -shared -m32 \
		-L ${TCL_TK_SHARED_LIBS} \
		-L ${DMH_SHARED_LIB}

DEST	      = .

EXTHDRS	      =

HDRS	      =

INSTALL	      = /usr/sbin/install

LIBRARY	      = facomcore.so

MAKEFILE      = Makefile

OBJS	      = facomcore.o

PRINT	      = pr

SHELL	      = /usr/bin/sh

SRCS	      = facomcore.c

SYSHDRS	      =

.c.o:
		$(CC) $(CFLAGS) $<

all:		$(LIBRARY)

$(LIBRARY):	integ
		@cp $(LIBRARY) $(SPECS_LIB)

clean:;		@rm -f $(OBJS) core

clobber:;	@rm -f $(OBJS) $(LIBRARY) core tags

depend:;	@mkmf -f $(MAKEFILE) ROOT=$(ROOT)

echo:;		@echo $(HDRS) $(SRCS)

extract:;	@ar x $(DEST)/$(LIBRARY)

index:;		@ctags -wx $(HDRS) $(SRCS)

integ:		$(OBJS)
		@rm -f $(LIBRARY)
		$(LD) $(LDFLAGS) -o $(LIBRARY) $(OBJS) $(LIBS) $(SYSLIBS)

install:	$(LIBRARY)
		@echo Installing $(LIBRARY) in $(DEST)
		@if [ $(DEST) != . ]; then \
		(rm -f $(DEST)/$(LIBRARY); $(INSTALL) -f $(DEST) $(LIBRARY)); fi

print:;		@$(PRINT) $(HDRS) $(SRCS)

tags:		$(HDRS) $(SRCS); @ctags $(HDRS) $(SRCS)

###
