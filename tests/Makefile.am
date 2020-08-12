AUTOMAKE_OPTIONS = subdir-objects 

TESTS = protocol
check_PROGRAMS = protocol

protocol_SOURCES = protocol.c

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

protocol_CFLAGS = -I/usr/include \
               -I$(includedir)

protocol_LDADD = ${PROTOCOL_LIBS} \
              ../src/protocol.o \
              -lcheck -lsubunit -lm -lrt -lpthread
