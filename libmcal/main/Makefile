CC = ${COMPILER}
INCLUDE = ${INCLUDES}

mcal-main: 
	@${CC} ${INCLUDE} -M *.c > depend.d
	@make -f Makefile.act

clean:
	rm -f *.o

distclean:
	rm -f *.o
	
