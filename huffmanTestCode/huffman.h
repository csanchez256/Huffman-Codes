#ifndef HUFFMAN_H
#define HUFFMAN_H

void getFrequency();


/* Define Huffman Tree Node */
struct HuffmanTreeNode
{
  int symbols;
  unsigned frequency;
  struct HuffmanTreeNode *next, *left, *right;
};

/* Defines a heap structure for the priority queue. This will be a collection */
/* of Tree nodes */

struct MiniHeap
{
  int front, back;
  unsigned long size;
  int capacity;
  struct HuffmanTreeNode **symbolsAndFreqs; /* pointer to a pointer */
  struct HuffmanTreeNode **priorityQueueList;
};

/* Define a tree node that will contain values frequencies and symbols */
struct HuffmanTreeNode* createNode(int symbols, unsigned long frequency);

/* Defines a Mini heap that will be used to create the priority queue */
struct MiniHeap* createMiniHeap(unsigned capacity);

/* This stores the actual values from frequencies and symbols into the Tree Nodes */
struct MiniHeap* buildMiniHeap(int symbols[], unsigned long frequency[], int size);

/* This function will sort the frequencies in the mini heap, into a priority queue */
struct HuffmanTreeNode* priorityQueue(struct HuffmanTreeNode* head,
                   char symbol, unsigned long freq);

/* Utility function to print the sorted heap */
void printList(struct HuffmanTreeNode* head);

/* Construct a huffman tree */
struct HuffmanTreeNode* buildHuffmanTree(int symbols[], unsigned long frequency[], int size);


#endif
