export INCLUDES=" -I./ -I${MOSAPP_LIBMCAL_HOME}/include \
-I${MOSAPP_LIBMCAL_HOME}/main \
-I${MOSAPP_LIBC_HOME}/include/ -I${MOSAPP_LIBC_HOME}/sysdeps/mos/common/ "

#C_FLAGS=" -c -O2 -Wall -ffreestanding -pedantic "
export C_FLAGS=" -c -Wall -O2 -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -shared -fPIC -D__GCC__ "

export C_FLAGS_OUT=" -Wall -O2 -nostdlib -nodefaultlibs -ffreestanding -nostdinc -nostartfiles -Wl,-shared -Wl,-fPIC -D__GCC__ "
