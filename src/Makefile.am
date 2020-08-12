AUTOMAKE_OPTIONS = subdir-objects 

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

bin_PROGRAMS = server

server_SOURCES = worker.c \
								 protocol.c \
								 main.c

server_LDADD = ${SERVER_LIBS} -lpthread
