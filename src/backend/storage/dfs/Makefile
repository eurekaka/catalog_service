#
# Makefile for storage/ipc
#
# $PostgreSQL: pgsql/src/backend/storage/ipc/Makefile,v 1.20 2007/01/20 17:16:12 petere Exp $
#

subdir = src/backend/storage/dfs
top_builddir = ../../../..
include $(top_builddir)/src/Makefile.global

# seems to be required 1999/07/22 bjm
ifeq "$(findstring alpha,$(host_cpu))" "alpha"
ifeq "$(GCC)" "yes"
override CFLAGS+= -fno-inline
endif
endif

OBJS = s3api.o

all: SUBSYS.o

SUBSYS.o: $(OBJS)
	$(LD) $(LDREL) $(LDOUT) SUBSYS.o $(OBJS)

clean: 
	rm -f SUBSYS.o $(OBJS)
