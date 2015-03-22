COMPILER=gcc
export COMPILER

MOS_HOME=$HOME/MOSDev
export MOS_HOME

MOSAPP_LIBMCAL_HOME=$MOS_HOME/MOSApps/libmcal
export MOSAPP_LIBMCAL_HOME

MOSAPP_LIBC_HOME=$MOS_HOME/MOSApps/libc
export MOSAPP_LIBC_HOME

INCLUDES=" -I./ -I${MOSAPP_LIBMCAL_HOME}/include \
-I${MOSAPP_LIBMCAL_HOME}/main \
-I${MOSAPP_LIBC_HOME}/include/ -I${MOSAPP_LIBC_HOME}/sysdeps/mos/common/ "
export INCLUDES

#C_FLAGS=" -c -O2 -Wall -ffreestanding -pedantic "
C_FLAGS=" -c -Wall -O2 -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -shared -fPIC -D__GCC__ "
export C_FLAGS

C_FLAGS_OUT=" -Wall -O2 -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -shared -fPIC -D__GCC__ "
export C_FLAGS_OUT

