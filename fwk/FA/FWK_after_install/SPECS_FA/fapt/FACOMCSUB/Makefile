SPECS_INCLUDE = /opt/SPECS/sys/include

SPECS_LIB     = /opt/SPECS/usr/lib

RMB_INCLUDE   = /opt/rmb/include

HP4070_INCLUDE= /opt/hp4070/include

SICL_INCLUDE  = /opt/sicl/include

SYSLIBS	      = 

CC	      = /usr/bin/gcc

CFLAGS	      = -g -c -fPIC -m32 \
		-I ${RMB_INCLUDE} \
		-I ${SPECS_INCLUDE} \
		-I ${HP4070_INCLUDE} \
		-I ${SICL_INCLUDE}

LD	      = /usr/bin/gcc

LDFLAGS	      = -shared -m32

DEST	      = .

EXTHDRS	      =

HDRS	      = FACOMCSUB.h

INSTALL	      = /usr/sbin/install

LIBRARY	      = FACOMCSUB.so

CSUBLIBRARY   = FACOMCSUB.usrlib

MAKEFILE      = Makefile

OBJS	      = FACOMCSUB.o

PRINT	      = pr

SHELL	      = /usr/bin/sh

SRCS	      = FACOMCSUB.c

RMBBUILD      = /opt/rmb/bin/rmbbuildc

RMBCSUBSCR    = fa_stream

RMBCSUBLOG    = /tmp/rmbbuildc.log

.c.o:
		rm -f $(@); $(CC) $(CFLAGS) $< || (rm -f $@)

all:		$(LIBRARY)

$(LIBRARY):	integ
		@cp $(LIBRARY) $(SPECS_LIB)
		@cp $(CSUBLIBRARY) $(SPECS_LIB)

clean:;		@rm -f $(OBJS) core

clobber:;	@rm -f $(OBJS) $(LIBRARY) $(CSUBLIBRARY) core tags

depend:;	@mkmf -f $(MAKEFILE) ROOT=$(ROOT)

echo:;		@echo $(HDRS) $(SRCS)

extract:;	@ar x $(DEST)/$(LIBRARY)

index:;		@ctags -wx $(HDRS) $(SRCS)

integ:		$(OBJS)
		@rm -f $(LIBRARY)
		$(LD) $(LDFLAGS) -o $(LIBRARY) $(OBJS) $(LIBS) $(SYSLIBS)
		$(RMBBUILD) < $(RMBCSUBSCR) > $(RMBCSUBLOG)

install:	$(LIBRARY)
		@echo Installing $(LIBRARY) in $(DEST)
		@if [ $(DEST) != . ]; then \
		(rm -f $(DEST)/$(LIBRARY); $(INSTALL) -f $(DEST) $(LIBRARY)); fi

print:;		@$(PRINT) $(HDRS) $(SRCS)

tags:		$(HDRS) $(SRCS); @ctags $(HDRS) $(SRCS)

###
