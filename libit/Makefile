CC = ${COMPILER}
AR = ar
INCLUDE = ${INCLUDES}

CFLAGS = ${C_FLAGS} ${INCLUDE}

it:
	${CC} ${C_FLAGS_OUT} ${INCLUDES} -c it.c
	${AR} -rf libit.a it.o
	
clean:
	rm -f *.o *.a

distclean:
	rm -f *.o *.a
