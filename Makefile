CC = gcc
.PHONY: all clean test

all: sed_simplified

clean:
	rm -f file.o main.o sed_simplified

main.o: main.c
	$(CC) -c main.c -Wall -Wextra

file.o: file.c
	$(CC) -c file.c -Wall -Wextra

sed_simplified: main.o file.o
	$(CC) main.o file.o -o sed_simplified -Wall -Wextra

test: sed_simplified
	./sed_simplified input.txt -r "old text" "new text"
	./sed_simplified input.txt -d "text to delete"
	./sed_simplified input.txt -i -f "insert text front"
	./sed_simplified input.txt -i -b "insert text back"
