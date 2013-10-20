CC = gcc
CFLAGS = -Wall -c

tarea1: main.o filters.o
	$(CC) $^ -o $@

filters.o: src/filters.c include/filters.h
	$(CC) $(CFLAGS) $<

main.o: src/main.c include/main.h
	$(CC) $(CFLAGS) $<

clean:
	rm -rf Informacion
	find . -name '*.o' -type f -delete
	rm -f tarea1