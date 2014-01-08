CC=g++
C-FLAGS= -std=c++1y -c -I./../../

all: generating.o treenumber.o main.o 
	$(CC) generating.o main.o treenumber.o -o madeup.out

treenumber.o:
	$(CC) $(C-FLAGS) treenumber.cpp -o treenumber.o

generating.o:
	$(CC) $(C-FLAGS) generating.cpp -o generating.o

main.o:
	$(CC) $(C-FLAGS) main.cpp -o main.o

clean:
	rm *.o
	rm *.out 
