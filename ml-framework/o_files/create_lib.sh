gcc -c ../src/matrix/*.c -I ../include -Wall
gcc -c ../src/vector/*.c -I ../include -Wall
gcc -c ../src/operations/*.c -I ../include -Wall
ar rcs ../lib/libmlfw.a *.o