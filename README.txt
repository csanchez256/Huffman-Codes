As of now, the program does not yet encode or decode any files. It prints a frequency
table with the huffman codes of each character that is read in.

To run the program type in the terminal:

	 make huffencode

Then type in the terminal:

	./huffencode <input file> <output file>

Example: ./huffencode ugly.txt test.out

The expected output will be a table of symbols, frequencies, codes, and total 
characters.

Note I updated the given Makefile to include huffman_helper.c, which is the file that
has most of the helper functions
