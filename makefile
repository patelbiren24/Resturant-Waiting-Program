CC=gcc

run.exe: source2.o source1.o base.o
	$(CC) -o run.exe source2.o source1.o base.o

source2.o:  header.h source2.c
	$(CC) -c source2.c

source1.o:  header.h source1.c
	$(CC) -c source1.c

base.o:  header.h base.c
	$(CC) -c base.c


clean:
	rm *.o run.exe
