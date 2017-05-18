/******************************************************************************
* Christopher Sanchez; CS241; Lab-08; huffman_helper.c        
* This file contains the helper functions for huffman.c
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "huffman.h" 

/******************************************************************************
* create a linked list of frequencies and symbols. symbolsAndFreqs[] is an 
* array that has a node (made of symbols and frequencies) in each index       
*                                      
* CALLS: createNode()       
******************************************************************************/
struct MiniHeap* constructList(unsigned char symbols[],unsigned long frequency[],int size)
{
  int i;
  struct MiniHeap* minHeap = createMiniHeap(size);
  for(i = 0; i < size; i++)
  {
    minHeap->symbolsAndFreqs[i] = createNode(symbols[i], frequency[i]);
  }
  return minHeap; 
} 

/******************************************************************************
* Utility functionS to grab the first lowest frequency Or "Pop"  the first 
* couple of nodes                                             
******************************************************************************/
struct  HuffmanTreeNode* removeFirstNode(struct HuffmanTreeNode* head)
{
  struct HuffmanTreeNode* current = head;
  if(head == NULL) return 0;
  else
  {
   /* if(DEBUG) printf("removing nodes\n");*/
    head = (current)->next;
    return head;
  }
}
/* function performs same operation as above  */
struct  HuffmanTreeNode* removeSecondNode(struct HuffmanTreeNode* head)
{
  struct HuffmanTreeNode* current = head;
  if(head == NULL) return 0;
  else
  {
    head = (current)->next;
    return head;
  }
}

/* Utility function to print the sorted linked list*/
void printList(struct HuffmanTreeNode* head)
{
  struct HuffmanTreeNode* current = head;
  while (current != NULL)
  {
    printf("(%c:%d)",current->symbols,current->frequency);
    current = current->next;
  }
  printf("\n\n");
}

/******************************************************************************
* helper function to print the codes of each symbol    
******************************************************************************/
void printArrayHelper(int array[],int i,FILE* out)
{
  int n;
  /*struct HuffmanTreeNode* codes[8];*/
  for(n = 0; n < i; ++n)
  {
    printf("%d", array[n]);
    fprintf(out,"%d", array[n]);
  }
  printf("\n");
  fprintf(out,"\n"); 
}

/******************************************************************************
* Check if node is a leaf. The logic here is that if both the left AND right        
* children are NULL pointers, then the conclusion is that there are no children
* and the node itself has to be a leaf (last remaining node on the branch)
******************************************************************************/
int checkIfNodeIsALeaf(struct HuffmanTreeNode* root)
{
  return ( (root->left == NULL) && (root->right == NULL) );
}

/* Function to free allocated memory when building tree */
void freeTree(struct HuffmanTreeNode* root)
{
  if(root != NULL)
  {
    freeTree(root->left);
    freeTree(root->right);
    free(root);
  }
}

/* Function to free allocated memory from making list */
void freeList(struct HuffmanTreeNode* head)
{
  struct HuffmanTreeNode* current = head;
  if(current != NULL)
  {
    freeList(current->next);
    current->next = NULL;
    free(current);
  }
}



