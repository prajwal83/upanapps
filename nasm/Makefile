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
LD_FLAGS := $(shell . $(UPANAPPS_HOME)/setup.sh; env | grep "\<LD_FLAGS\>" | cut -d"=" -f2)
CC := $(shell . $(UPANAPPS_HOME)/setup.sh; env | grep "\<CC\>" | cut -d"=" -f2)
NASM_OBJS := $(patsubst %.c,%.o,$(shell find nasm_src -name *.c))
NDISASM_OBJS := $(patsubst %.c,%.o,$(shell find ndisasm_src -name *.c))

build: subdir nasm ndisasm

subdir:
	cd nasm_src && make
	cd ndisasm_src && make

nasm: ${NASM_OBJS}
	${CC} ${LD_FLAGS} ${NASM_OBJS} -o nasm -e main -L${UPANAPPS_HOME}/libc -lc

ndisasm: ${NDISASM_OBJS}
	${CC} ${LD_FLAGS} ${NDISASM_OBJS} -o ndisasm -e main -L${UPANAPPS_HOME}/libc -lc

clean:
	cd nasm_src && make clean
	cd ndisasm_src && make clean

distclean:
	cd nasm_src && make clean
	cd ndisasm_src && make clean
	rm -f nasm
	rm -f ndisasm
