/*****************************************************************************
* Christopher Sanchez; CS241; Lab-08; huffman.c
*
* The program in huffencode.c takes two command line arguments. The first is 
* the name of the file to encode and the second is the name of the file where 
* the encoded data will be written. This program demonstrates how to read in
* characters from a file, sort them based on frequencies the letters occur, 
* and then build a binary tree with the data.
*                                                                          
* RUN WITH: 
* ~$ make huffencode, huffdecode                                     
* ~$ ./huffencode <test file> <output file>                        
*                                                                           
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

#define DEBUG 0

unsigned char *symbols;
unsigned long *frequency;
int array[256];
int eightBitArray[8];


/******************************************************************************
* Construct a Huffman tree node. Memory is allocated for symbols, frequencies,        
* left node, right node, and next node.                                     
******************************************************************************/
struct HuffmanTreeNode* createNode(unsigned char symbols, unsigned long frequency)
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

/******************************************************************************
* Defines a Mini heap that will be used to create the priority queue       
*                                                                          
******************************************************************************/
struct MiniHeap* createMiniHeap(unsigned capacity)
{
  struct MiniHeap* minHeap = (struct MiniHeap*)malloc(sizeof(struct MiniHeap));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->symbolsAndFreqs=(struct HuffmanTreeNode**)malloc(minHeap->capacity* 
                                              sizeof(struct HuffmanTreeNode*)); 
  return minHeap;
}

/******************************************************************************
* Creates Tree nodes assigning the left and right childten to the parent.       
*                                                                            
******************************************************************************/
struct HuffmanTreeNode* treeConstruction(struct HuffmanTreeNode* head,
                                                unsigned char symbol, unsigned long freq)
{
  struct HuffmanTreeNode* tNode = createNode(symbol,freq);
  tNode->frequency = (head->frequency) + (head->next->frequency);
  tNode->symbols = head->next->symbols;
  tNode->left = head;
  tNode->right = head->next;
  tNode->next = NULL;
  
  return tNode;
}

/******************************************************************************
* This   function will sort the nodes in minHeap (symbols and frequencies)  
* in ascending order. If frequencies match, the tie breaker is the order of        
* symbols                                                                          
******************************************************************************/
struct HuffmanTreeNode* priorityQueue(struct HuffmanTreeNode* head,
                   unsigned char symbol, unsigned long freq)
{
  struct HuffmanTreeNode* newNode = createNode(symbol,freq);
  struct HuffmanTreeNode* currentNode = head;

  if(currentNode == NULL || newNode->frequency < currentNode->frequency)
  {
    /* insert new node before current node */
    newNode->next = currentNode;
    return newNode;
  }

  else if (newNode->frequency > currentNode->frequency) 
  {
    /*loop while newnode symbol and frequency is greater*/
    while(currentNode->next != NULL &&
           (currentNode->next->frequency <= newNode->frequency) &&
           (currentNode->next->symbols <= newNode->symbols))
    {
      currentNode = currentNode->next; /*Update head pointer*/
    }
    /*Insert node after the current node*/
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    return head;
  }

  /*Tie breaker for symbols that are the same*/
  else if( newNode->frequency == currentNode->frequency)
  {
    if(newNode->symbols < currentNode->symbols)
    {
      newNode->next = currentNode->next;
      currentNode->next = newNode;
      return head;
    }
    else
    {
      /*loop while next newNode symbol and frequency is greater*/
      while(currentNode->next != NULL &&
            (currentNode->next->symbols <= newNode->symbols) &&
            (currentNode->next->frequency <= newNode->frequency))
      {
        currentNode = currentNode->next;
      }
        newNode->next = currentNode->next;
        currentNode->next = newNode;
        return head;
    }
  } 
  else return head; 
}
  
/******************************************************************************
* This function will insert the treeNode back into the priority queue. The        
* order depends on the frequencies. If frequencies are the same the tie beaker
* are the symbols
******************************************************************************/
struct HuffmanTreeNode* insertTreeNode(struct HuffmanTreeNode* head,
                  unsigned char symbol, unsigned long freq, struct HuffmanTreeNode* leaf)
{
  struct HuffmanTreeNode* currentNode = head;
  struct HuffmanTreeNode* newNode = leaf;
  
  if(DEBUG) printf("Inserting leaf into priority queue\n");

  /* create first node */
  if(currentNode == NULL || newNode->frequency < currentNode->frequency)
  {
    newNode->next = currentNode;
    return newNode;
  }

  if (newNode->frequency > currentNode->frequency) 
  {
    /*loog while the frequency of newNode is greater than next node*/
    while(currentNode->next != NULL &&
	  (newNode->frequency > currentNode->next->frequency))
    {
      /*update the head pointer*/
      currentNode = currentNode->next;
    }
  }
  /* stop and make sure there aren't any nodes ahead with the same frequency */
  if(currentNode->next != NULL &&
         (newNode->frequency == currentNode->next->frequency))
  {
      /*loop while the new node's frequencies are greater*/
    while((currentNode->next != NULL) &&
          (newNode->symbols > currentNode->next->symbols) &&                     
           (newNode->frequency == currentNode->next->frequency))
    {
      currentNode = currentNode->next;
    } 
      /*insert after current node*/
      newNode->next = currentNode->next;
      currentNode->next = newNode;
      return head;    
    }

   else
   {
     newNode->next = currentNode->next;
     currentNode->next = newNode; 
  }
  return head; 
}

/*****************************************************************************
* This function will walk down the tree and generate codes 
* Very similar to printLeaves() on slides
* Recursion is used here to visit the left and right child nodes of each 
* parent. A 0 represents the left node, 1 represents the right. Conceptually
* this looks like an actuall tree. The function recurs until the max depth
* level is reached, on its way back, it will check the right nodes. The base
* case is the check if the node is a "leaf", meaning that its children are non
* existent
* CALLS: checkIfNodeIsALeaf(), printArrayHelper()
******************************************************************************/
void treeTraversal(struct HuffmanTreeNode* root,FILE* out,int array[],
                                                              int index,char j)
{
  if(root != NULL)
  {
    if(root->left)
    {
      array[index] = 0;
      treeTraversal(root->left,out,array,index+1,j);
    }
    
    if(root->right)
    {
      array[index] = 1;
      treeTraversal(root->right,out,array,index+1,j);
    }
    
    if(checkIfNodeIsALeaf(root))
    {
      /* j is a character value from 32 - 126, if 'j' happens to equal a leaf*/
      /* then we print the code for that character. This variable is in      */
      /* encodeFile()                                                        */
      if(j == root->symbols)
      { 
        printArrayHelper(array,index,out);
      }
    }
  }  
}

/******************************************************************************
* Driver function that organizes the priority queue, when the tree is built, 
* poping the nodes in the queue, and inserting the treenodes back into the 
* queue.
*
* Calls: priorityQueue(), printList(), treeConstruction(), removeFirstNode()
*        removeSecondNode(), insertTreeNode()                                  
******************************************************************************/
struct HuffmanTreeNode* buildHuffmanTree(unsigned char symbols[], 
                                        unsigned long frequency[], int size)
{
  int i;
  unsigned long freq;
  unsigned char symbol;

  struct MiniHeap* minHeap = constructList(symbols,frequency,size);
  struct HuffmanTreeNode* head = NULL;
  struct HuffmanTreeNode* leaf = NULL;

  for(i = 0; i < size; i++)
  {
    /* With each iteration, we are accessing the symbols and frequencies */
    freq = minHeap->symbolsAndFreqs[i]->frequency;
    symbol = minHeap->symbolsAndFreqs[i]->symbols;

    /* Now we will construct the priority queue with linked list */
    head = priorityQueue(head,symbol,freq);
  }

  if(DEBUG) printList(head);

    while(head->next != NULL)
    {
      /*create the node, add the frequencies */
      leaf = treeConstruction(head,symbol,freq);

        /* remove the 1st and 2nd nodes */
      if(DEBUG)printf("pop 1st and 2nd node\n");
      head = removeFirstNode(head);
      head = removeSecondNode(head);
          
      if(DEBUG)
      {
	printList(head);
        printf("\nTree Node ");
      }
      if(DEBUG) printList(leaf);
    
      /* insert leaf back into priority queue */
      head = insertTreeNode(head,symbol,freq,leaf);
      if(DEBUG) printList(head);    
  }
 /* free(head);*/
  return leaf;
}

/******************************************************************************
* Reads in commandline input file and calculates the frequency that each        
* character occurs.
*         
* Calls: buildHuffmanTree(), treeTraversal(),                              
******************************************************************************/
void encodeFile(FILE* in, FILE* out, int printTable)
{
  int c = 0;
  int i,j = 0;
  int frequencyIndex = 0;
  int fIndex = 0;
  int charCount = 0;
  unsigned long occurances[256];

  
  int index = 0; 
  struct HuffmanTreeNode* root = NULL; 

  /* fill occurances with 0's */
  for(i = 0; i < 256; i++)
  {
    occurances[i] = 0;  
  }

  /* initialize array */
  for(i = 0;i<256;i++)
  {
    eightBitArray[i] = 0;
  }
  
  while ((c = getc(in)) != EOF)
  {
    /**************************************************************************
    * The index 'c' will actually  be represented as ascii character values   
    * When iterating through array below                                       
    * As long as the character is valid, increment each index for the frequency 
    **************************************************************************/
    occurances[c] = occurances[c] + 1;
    ++charCount;   
  }
 
  /* Allows us to compute the size of frequency and symbols arrays */
  for (i = 0; i < 256; i++)
  {
    if(occurances[i] > 0) fIndex++;
  }

  /* dynamically allocate memory for arrays */
  symbols = (unsigned char *)malloc(sizeof(unsigned char)*fIndex);
  frequency = (unsigned long *)malloc(sizeof(unsigned long)*fIndex);
 
  /* Stores characters from ascii range [<space> to ~] or [32 - 126] */
  for (i = 0; i < 256; i++)
  {
    if(occurances[i] > 0)          /* we are not interested in 0 frequencies */
    {
      symbols[frequencyIndex] = (char)i;          /* load symbols into array */
      frequency[frequencyIndex] = occurances[i];  /* load frequncies         */
      frequencyIndex++;
    } 
  }

  /* Build Huffman Tree */
  root = buildHuffmanTree(symbols,frequency,frequencyIndex);

  /* Note printf() will write to stdout, while fprintf() will use the FILE* 
    * out variable to write the output stream to a text file specified in 
    * the command line arguments                                          */
  printf("Symbol\tFreq\tCode\n");
  fprintf(out,"Symbol\tFreq\tCode\n");

  /*Iterate and print the symbols, frequencies, Code*/
  for (j = 0; j < 256; j++)
  {
    if(occurances[j] > 0) /*So we don't use 0 frequencies*/          
    {
      if(j <= 32 || j >= 127) 
      {
        printf("=%d",j);
        fprintf(out,"=%d",j);
      }

      printf("%c\t%lu\t",j,occurances[j]);
      fprintf(out,"%c\t%lu\t",j,occurances[j]);
      /* Traverse tree and print codes */
      treeTraversal(root,out,array,index,j); 
    } 
  }
  printf("Total chars = %d\n",charCount);
  fprintf(out, "Total chars = %d\n",charCount);

  free(symbols);
  free(frequency);
  freeTree(root);
}



