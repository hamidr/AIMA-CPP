CC=g++
C-FLAGS= -std=c++1y -c -I./../../

all: missiocanib.o main.o 
	$(CC) main.o missiocanib.o -o mcb.out

missiocanib.o:
	$(CC) $(C-FLAGS) missiocanib.cpp -o missiocanib.o

main.o:
	$(CC) $(C-FLAGS) main.cpp -o main.o

clean:
	rm *.o
	rm mcb.out
