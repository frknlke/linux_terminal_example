a.out: main.o commands.o
	gcc main.o commands.o -o a.out

main.o: main.c main.h
	gcc -c main.c -o main.o

commands.o: commands.c commands.h
	gcc -c commands.c -o commands.o

clean:
	rm *.o a.out