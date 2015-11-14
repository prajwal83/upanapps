apps:
	cd libc && make
	cd libmterm && make
	cd libmcal && make
	cd libm && make
	cd libit && make
	cd nasm && make
	cd editor && make
	cd shell && make
	
clean:
	cd libc && make clean
	cd libmterm && make clean
	cd libmcal && make clean
	cd libm && make clean
	cd libit && make clean
	cd nasm && make clean
	cd editor && make clean
	cd shell && make clean

distclean:
	cd libc && make distclean
	cd libmterm && make distclean
	cd libmcal && make distclean
	cd libm && make distclean
	cd libit && make distclean
	cd nasm && make distclean
	cd editor && make distclean
	cd shell && make distclean
