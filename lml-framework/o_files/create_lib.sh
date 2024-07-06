gcc -c ../src/matrix/*.c -I ../include/
gcc -c ../src/vector/*.c -I ../include/
gcc -c ../src/operations/*.c -I ../include/
gcc -c ../src/set/*.c -I ../include/
gcc -c ../src/encoder/*.c -I ../include/
gcc -c ../src/scale/*.c -I ../include/
ar rcs ../lib/liblml.a *.o