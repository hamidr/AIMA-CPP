CC=g++
C-FLAGS= -std=c++1y -c -I./../../

all: romaniacities.o main.o 
	$(CC) main.o romaniacities.o -o cities.out

romaniacities.o:
	$(CC) $(C-FLAGS) romaniacities.cpp -o romaniacities.o

main.o:
	$(CC) $(C-FLAGS) main.cpp -o main.o

clean:
	rm *.o
	rm cities.out 
