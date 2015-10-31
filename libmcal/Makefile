CC = ${COMPILER}

MAIN = ${MOSAPP_LIBMCAL_HOME}/main

INCLUDE = ${INCLUDES}

CFLAGS = ${C_FLAGS} ${INCLUDE}

libc:
	cd ${MAIN} && make
	
	@make -f Makefile.act 
	@cp libmcal.so ${MOS_HOME}/tools/yard/
	
clean:
	cd ${MAIN} && make clean

distclean:
	cd ${MAIN} && make distclean

	rm -f libmcal.so
	find . -name "depend.d" -exec rm {} \;

