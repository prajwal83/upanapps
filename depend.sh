. ${UPANAPPS_HOME}/setup.sh $@

> depend.d
for i in `ls *.c 2> /dev/null`
do
	obj=${i%.*}.o
	$CC ${INCLUDE} -M $i >> depend.d
	echo "\t@echo \"compiling $i...\"" >> depend.d
	echo "\t@$CC ${CFLAGS} ${INCLUDE} $i -o ${obj}" >> depend.d
done
