OBJS	= affichage.o fichiers.o fir.o iir.o integration.o lecture.o main.o mesure.o
SOURCE	= affichage.c fichiers.c fir.c iir.c integration.c lecture.c main.c mesure.c
HEADER	= affichage.h define.h fichiers.h fir.h iir.h integration.h lecture.h mesure.h
OUT	= oxymetre
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

affichage.o: affichage.c
	$(CC) $(FLAGS) affichage.c -std=c99

fichiers.o: fichiers.c
	$(CC) $(FLAGS) fichiers.c -std=c99

fir.o: fir.c
	$(CC) $(FLAGS) fir.c -std=c99

iir.o: iir.c
	$(CC) $(FLAGS) iir.c -std=c99

integration.o: integration.c
	$(CC) $(FLAGS) integration.c -std=c99

lecture.o: lecture.c
	$(CC) $(FLAGS) lecture.c -std=c99

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

mesure.o: mesure.c
	$(CC) $(FLAGS) mesure.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)