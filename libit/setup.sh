COMPILER=gcc
export COMPILER

MOS_HOME=$HOME/MOSDev
export MOS_HOME

MOSAPP_LIBIT_HOME=$MOS_HOME/MOSApps/libit
export MOSAPP_LIBIT_HOME

MOSAPP_LIBC_HOME=$MOS_HOME/MOSApps/libc
export MOSAPP_LIBC_HOME

INCLUDES=" -I${MOSAPP_LIBC_HOME}/include/ -I${MOSAPP_LIBC_HOME}/sysdeps/mos/common/ "
export INCLUDES

#C_FLAGS=" -c -O2 -Wall -ffreestanding -pedantic "
C_FLAGS=" -c -Wall -O2 -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -D__GCC__ "
export C_FLAGS

C_FLAGS_OUT=" -Wall -O2 -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -D__GCC__ "
export C_FLAGS_OUT

