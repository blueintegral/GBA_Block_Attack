#include <stdlib.h>
#include <stdio.h>
#include "narytree.h"

NaryNode *createNaryNode(Data data, unsigned int children)
{
  // Allocate the structure
  NaryNode *node = (NaryNode*)calloc(1, sizeof(NaryNode));

  // Set the elements of the structure
  node->data = data;
  node->n = children;
  node->child = (NaryNode**)calloc(children, sizeof(NaryNode*));

  // Return the structure we just allocated
  return node;
}

void appendChild(NaryNode *root, NaryNode *newNode)
{
  // Increment the degree of the node
  root->n++;

  // Reallocate the child array (N children in the CHILD array)
  root->child = (NaryNode**)realloc(root->child, (root->n)*sizeof(NaryNode*));

  // Add the newNode into the CHILD array and increment degree
  root->child[root->n-1] = newNode;

  /* Could also be written:
    // Reallocate the child array (N children in the CHILD array)
    root->child = (NaryNode**)realloc(root->child, (root->n+1)*sizeof(NaryNode*));

    // Add the newNode into the CHILD array and increment degree
    root->child[root->n++] = newNode;
  */
}

void insertChild(NaryNode *root, unsigned asIndex, NaryNode *newNode)
{
  int i;

  // Expand the child array
  if (root->n <= asIndex)
  { // The child array needs to be expanded more
    root->child = (NaryNode**)realloc(root->child, (asIndex+1)*sizeof(NaryNode*));
    // The extra spaces need to be NULL'd out (realloc doesn't do this)
    while (root->n <= asIndex)
      root->child[root->n++] = NULL;
  }
  else
  {
    // Increment the degree
    root->n++;
    // Reallocate the space
    root->child = (NaryNode**)realloc(root->child, root->n*sizeof(NaryNode*));
  }

  // Bump back all children
  for (i = root->n-2; i >= 0 && i >= (int)asIndex; --i)
    root->child[i+1] = root->child[i];

  root->child[asIndex] = newNode;
}

void freeNaryTree(NaryNode *root, DataFreeFunc fr)
{
  unsigned i;

  // Terminating condition
  if (root == NULL)
    return;

  // Recursively free all children
  for (i = 0; i < root->n; ++i)
    freeNaryTree(root->child[i], fr);

  // Free the data if necessary
  if (fr)
    fr(root->data);

  free(root);
}

unsigned sizeOfNaryTree(NaryNode *root)
{
  unsigned size = 0;
  unsigned i;
  
  if (root)
  {
    size++;
    for (i = 0; i < root->n; ++i)
      size += sizeOfNaryTree(root->child[i]);
  }

  return size;
}

typedef struct _nodewithlevel {
  NaryNode *node;
  unsigned level;
} NaryNodeLevel;

void printNaryTree(NaryNode *root, DataPrintFunc print)
{
  unsigned in = 0;
  unsigned out = 0;
  unsigned size = sizeOfNaryTree(root);
  NaryNodeLevel *levels = (NaryNodeLevel*)calloc(size, sizeof(NaryNodeLevel));

  // Enqueue the root
  levels[in].node = root;
  levels[in].level = 0;
  in++;

  while (in > out && out < size)
  {
    unsigned i;

    if (levels[out].node)
    {
      // Enqueue children
      for (i = 0; i < levels[out].node->n; ++i)
      {
        if (levels[out].node->child[i] == NULL) continue;
        levels[in].node = levels[out].node->child[i];
        levels[in].level = levels[out].level + 1;
        in++;
      }
     
      // Print out the data of this node (TODO: PADT?)
      printf("%d: ", levels[out].level);
      print(levels[out].node->data);
      printf("\n");
    }

    out++;
  }
  free(levels);
}

Data createIntData(int i)
{
  int *data = (int*)calloc(1, sizeof(int));
  data[0] = i;
  return data;
}

void printIntData(Data data)
{
  printf("%d", *(int*)data);
}
