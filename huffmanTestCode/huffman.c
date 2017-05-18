/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int symbols[4];
unsigned long frequency[4];
int size = 4;


/****************************************/
/* construct a Huffman tree node        */
/*                                      */
/*                                      */
/****************************************/
struct HuffmanTreeNode* createNode(int symbols, unsigned long frequency)
{
  struct HuffmanTreeNode* node =
   (struct HuffmanTreeNode*) malloc(sizeof(struct HuffmanTreeNode));
  node->symbols = symbols;
  node->frequency = frequency;
  node->left = NULL;
  node->right = NULL;
  node->next = NULL;
  return node;
}

/* Defines a Mini heap that will be used to create the priority queue */
struct MiniHeap* createMiniHeap(unsigned capacity)
{
  struct MiniHeap* minHeap = (struct MiniHeap*)malloc(sizeof(struct MiniHeap));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->symbolsAndFreqs=(struct HuffmanTreeNode**)malloc(minHeap->capacity * sizeof(struct HuffmanTreeNode*));
  return minHeap;
}

/* work on this later */
/* what you want is to create a linked list of frequencies and symbols */
struct MiniHeap* buildMiniHeap(int symbols[], unsigned long frequency[], int size)
{
  int i;
  struct MiniHeap* minHeap = createMiniHeap(size);
  for(i = 0; i < size; i++)
  {
    minHeap->symbolsAndFreqs[i] = createNode(symbols[i], frequency[i]);
  }
  return minHeap;
} 

/*****************************************************************************/
/* This   function will sort the nodes in minHeap (symbols and frequencies)  */
/* in ascending order                                                        */
/*                                                                           */
/*****************************************************************************/
struct HuffmanTreeNode* priorityQueue(struct HuffmanTreeNode* head,
                   char symbol, unsigned long freq)
{
  struct HuffmanTreeNode* newNode = createNode(symbol,freq);
  struct HuffmanTreeNode* currentNode;

  /*struct node* current*/
  /*insert in the beginning*/
  if(head == NULL || (head)->frequency >= newNode->frequency)
  {
    /* set the next pointer of the newNode, TO the current value of head */
    /* or "head is now newNode's 'next' field" */
    newNode->next = head;
    
    /* make the head pointer, point to the newNode */
    head = newNode;
  }
  else
  { 
    currentNode = head;

    /*locate the node before insertion*/
    while (currentNode->next != NULL && 
          (currentNode->next->frequency) < (newNode->frequency))
    {
      currentNode = currentNode->next;
    }
    newNode->next = currentNode->next;
    currentNode->next = newNode;
   }
 
  return head;
}

/* Utility function to print the sorted heap */
void printList(struct HuffmanTreeNode* head)
{
  struct HuffmanTreeNode* current = head;
  while (current != NULL)
  {
    printf("(%c:%d)",current->symbols,current->frequency);
    current = current->next;
  }
  printf("\n");
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
struct HuffmanTreeNode* buildHuffmanTree(int symbols[], unsigned long frequency[], int size)
{
  int i;
  unsigned long freq;
  char symbol;
  /* #1 create two empty queues */
  /* #2 create a leaf node for each symbol and put it into a queue     */
  struct MiniHeap* minHeap = buildMiniHeap(symbols,frequency,size);
  struct HuffmanTreeNode* head = NULL;

  /* this priority queue will be in increasing order so the nodes with */
  /* the lowest frequency will be the first ones to get summed         */
  for(i = 0; i < size; i++)
  {
    freq = minHeap->symbolsAndFreqs[i]->frequency;
    symbol = minHeap->symbolsAndFreqs[i]->symbols;

    head = priorityQueue(head,symbol,freq);

    printf("(%c:%lu)",symbol,freq);  
  }
  printf("\n");
  printList(head);
  /* #3 Dequeue the two nodes */

  /* # create an "internal" node by adding the two nodes with the lowest */
  /* frequencies together                                                */

  return head;
}

/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
void getFrequency()
{
  int c = 0;
  int i;
  int frequencyIndex = 0;
  int byteCount = 0;
  unsigned long occurances[256];

  for(i = 0; i < 256; i++)
  {
    occurances[i] = 0; 
  }

  while ((c = getchar()) != EOF)
  {
    if(c != '\0') byteCount++;

    if( c >= 32 && c <= 126) occurances[c] = occurances[c] + 1;   
  }

  for (i = 32; i < 127; i++)
  {
    if(occurances[i] > 0)
    {
      /*printf("char = %c, frequency = %lu\n",i,occurances[i]);*/

      /* we are loading arrays of 4 elements: frequencies, and symbols*/
      /* the actual program will be a lot larger */
      /* later you will have to use the whole ascii caracter table for the */
      /* frequencies, but for now, just hard code in values */
      symbols[frequencyIndex] = (char)i;
      frequency[frequencyIndex] = occurances[i];
      frequencyIndex++;
    } 
  }

  /*printf("byte count %d\n",byteCount);*/
}


int main()
{
  getFrequency();
  /*struct HuffmanTreeNode* root = buildHuffmanTree(symbols,frequency,size);*/
  buildHuffmanTree(symbols,frequency,size);
  return 0;
}

