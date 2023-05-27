all: Munchkin_memori

base.o: base.c
	gcc -c base.c -o base.o

maper.o: mapper.c base.h
	gcc -c maper.c -o mapper.o

whatif.o: whatif.c mapper.h
	gcc -c whatif.c -o whatif.o

save.o: save.c whatif.h
	gcc -c save.c -o save.o

gamplay.o: gamplay.c save.h
	gcc -c gamplay.c -o gamplay.o

main.o: main.c gamplay.h
	gcc -c main.c -o main.o

Munchkin_memori: main.o gamplay.o mapper.o save.o whatif.o base.o
	gcc main.o mapper.o gamplay.o save.o whatif.o base.o -o Munchkin_memori -lm

clean:
	rm -f *.o
	rm Munchkin_memori
