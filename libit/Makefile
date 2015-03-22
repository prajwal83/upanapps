CC = gcc
AR = ar
INCLUDE = ${INCLUDES}

CFLAGS = ${C_FLAGS} ${INCLUDE}

it:
	${CC} ${C_FLAGS_OUT} ${INCLUDES} -c it.c
	${AR} -rf libit.a it.o
	
clean:
	rm *.o *.a

distclean:
	rm *.o *.a
