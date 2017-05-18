/******************************************************************************
* Christopher Sanchez; CS241; Lab-08; huffman.h        
* This is the header file for huffman.c
******************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>

/* Defines Huffman Tree Node */
struct HuffmanTreeNode
{
  unsigned char symbols;
  unsigned frequency;
  struct HuffmanTreeNode *next, *left, *right;
  char *codes;
  int codeIndex;
};

/******************************************************************************
* Defines a heap structure for the priority queue. This will be a collection 
* of Tree nodes 
******************************************************************************/
struct MiniHeap
{
  unsigned long size;
  int capacity;
  struct HuffmanTreeNode **symbolsAndFreqs; /*pointer to a pointer*/
  struct HuffmanTreeNode **priorityQueueList;
};

/**************************************************************/
/* Huffman encode a file.                                     */
/* in -- File to encode.                                      */
/*       May be binary, so don't assume printable characters. */
/* out -- File where encoded data will be written.            */
/* printTable -- If not zero, print table of bytes,           */
/*               frequencies, and codes to standard output.   */
/**************************************************************/
void encodeFile(FILE* in, FILE* out, int printTable);

/***************************************************/
/* Decode a Huffman encoded file.                  */
/* in -- File to decode.                           */
/* out -- File where decoded data will be written. */
/***************************************************/
void decodeFile(FILE* in, FILE* out);

/* Define a tree node that will contain values frequencies and symbols */
struct HuffmanTreeNode* createNode(unsigned char symbols, unsigned long frequency);

/* Defines a Mini heap that will be used to create the priority queue */
struct MiniHeap* createMiniHeap(unsigned capacity);

/* This stores the actual values from frequencies and symbols into the Tree Nodes */
struct MiniHeap* constructList(unsigned char symbols[], unsigned long frequency[], int size);

/* This function will sort the frequencies in the mini heap, into a priority queue */
struct HuffmanTreeNode* priorityQueue(struct HuffmanTreeNode* head,
                   unsigned char symbol, unsigned long freq);


/* Utility function to grab the first lowest frequency */
struct HuffmanTreeNode* removeFirstNode(struct HuffmanTreeNode* head);

/* Utility function to grab the second lowest frequency */
struct HuffmanTreeNode* removeSecondNode(struct HuffmanTreeNode* head);

/****************************************************************************** 
* A utility function to assemble the binary tree, with the children being the 
* nodes we created in priorityQueue
******************************************************************************/
struct HuffmanTreeNode* treeConstruction(struct HuffmanTreeNode* head,
                           unsigned char symbol, unsigned long freq);

/* Utility function to insert the tree node back into priority queue */
struct HuffmanTreeNode* insertTreeNode(struct HuffmanTreeNode* head, unsigned char symbol, 
                              unsigned long freq, struct HuffmanTreeNode* leaf);

/* Utility function to print the sorted heap */
void printList(struct HuffmanTreeNode* head);


/* Walk down the binary tree and collect codes */
void treeTraversal(struct HuffmanTreeNode* root, FILE* out, int array[],int index,char j);

/* check if node is leaf */
int checkIfNodeIsALeaf(struct HuffmanTreeNode* root);

/* Helper function to print array in checkIfNodeIsALeaf() */
void printArrayHelper(int array[],int i,FILE* out);


/* Construct a huffman tree */
struct HuffmanTreeNode* buildHuffmanTree(unsigned char symbols[],unsigned long frequency[],int size);

/* free memory */
void freeTree(struct HuffmanTreeNode* root);

/* Function to free allocated memory from making list */
void freeList(struct HuffmanTreeNode* head);

#endif


