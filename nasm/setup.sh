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
COMPILER=gcc
export COMPILER

INCLUDES="-I${MOSAPP_NASM_HOME}/main \
\
-I${MOSAPP_LIBC_HOME}/include/ -I${MOSAPP_LIBC_HOME}/sysdeps/mos/common/ -I${MOSAPP_LIBC_HOME}/sysdeps/mos/common/bits/ "
export INCLUDES

#C_FLAGS=" -c -O2 -Wall -ffreestanding -pedantic "
C_FLAGS=" -c -Wall -O2 -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -D__GCC__ "
export C_FLAGS

C_FLAGS_OUT=" -Wall -O2 -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -D__GCC__ "
export C_FLAGS_OUT

