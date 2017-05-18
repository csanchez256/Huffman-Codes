all: huffencode huffdecode

clean:
	rm huffencode huffdecode

huffencode: huffman.h huffman.c huffencode.c huffman_helper.c
	gcc -Wall -ansi -pedantic -g -o huffencode huffman.c huffencode.c huffman_helper.c

huffdecode: huffman.h huffman.c huffdecode.c
	gcc -Wall -ansi -pedantic  -g -o huffdecode huffman.c huffdecode.c huffman_helper.c


