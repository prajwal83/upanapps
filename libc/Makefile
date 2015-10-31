#    Mother Operating System - An x86 based Operating System
#    Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
#                                                                            
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#                                                                            
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#                                                                            
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/
CC = i686-elf-gcc

LIB_PORT = ${MOSAPP_LIBC_HOME}/lib_port
CTYPE = ${MOSAPP_LIBC_HOME}/ctype
STRING = ${MOSAPP_LIBC_HOME}/string
SYS = ${MOSAPP_LIBC_HOME}/sys
STDIO = ${MOSAPP_LIBC_HOME}/stdio
STDLIB = ${MOSAPP_LIBC_HOME}/stdlib
STDCAL = ${MOSAPP_LIBC_HOME}/stdcal
DISPLAY = ${MOSAPP_LIBC_HOME}/display

INCLUDE = ${INCLUDES}

CFLAGS = ${C_FLAGS} ${INCLUDE}

libc:
	cd ${CTYPE} && make
	cd ${STRING} && make
	cd ${SYS} && make
	cd ${STDIO} && make
	cd ${STDLIB} && make
	cd ${STDCAL} && make
	cd ${DISPLAY} && make
	
	@make -f Makefile.act 
	@cp libc.so ${MOS_HOME}/tools/yard/
	
clean:
	cd ${CTYPE} && make clean
	cd ${STRING} && make clean
	cd ${SYS} && make clean
	cd ${STDIO} && make clean
	cd ${STDLIB} && make clean
	cd ${STDCAL} && make clean
	cd ${DISPLAY} && make clean

distclean:
	cd ${CTYPE} && make distclean
	cd ${STRING} && make distclean
	cd ${SYS} && make distclean
	cd ${STDIO} && make distclean
	cd ${STDLIB} && make distclean
	cd ${STDCAL} && make distclean
	cd ${DISPLAY} && make distclean

	rm -f libc.so
	find . -name "depend.d" -exec rm {} \;

