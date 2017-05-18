all: huffman

huffman: huffman.h huffman.c
	gcc -Wall -ansi -pedantic -g -o huffman huffman.c
	./huffman < test.txt > test.out
	cat test.out
clean:
	rm huffman
