CC = ${COMPILER}

SHELL = ${MOSAPP_HOME}/shell/
LIBC = ${MOSAPP_HOME}/libc/
INCLUDE = ${INCLUDES}

CFLAGS = ${C_FLAGS} ${INCLUDE}

mosapp:
	cd ${LIBC} && make
	cd ${SHELL} && make
	
#	@make -f Makefile.act flat

clean:
	cd ${LIBC} && make clean
	cd ${SHELL} && make clean

distclean:
	cd ${LIBC} && make distclean
	cd ${SHELL} && make distclean 

