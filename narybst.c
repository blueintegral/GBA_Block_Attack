#include <stdio.h>
#include "narytree.h"
#include "narybst.h"

NaryNode *insertBSTNode(NaryNode *root, NaryNode *newNode)
{
  // Terminating condition
  if (root == NULL)
    return newNode;

  // Recurse into subtrees
  if (*(int*)(newNode->data) < *(int*)(root->data))
    root->child[0] = insertBSTNode(root->child[0], newNode);
  else if (*(int*)(newNode->data) > *(int*)(root->data))
    root->child[2] = insertBSTNode(root->child[2], newNode);
  else // if (*(int*)(newNode->data) == *(int*)(root->data))
    root->child[1] = insertBSTNode(root->child[1], newNode);

  // Return the updated root node
  return root;
}

// In order traversal means LEFT, SELF, RIGHT
void printBSTInOrder(NaryNode *root)
{
  unsigned int count = 0;
  NaryNode *probe = root;

  // Terminating condition
  if (root == NULL)
    return;

  // Left
  printBSTInOrder(root->child[0]);

  // Self
  while (probe)
  {
    count++;
    probe = probe->child[1];
  }
  printf("[%d (%d)]\n", *(int*)(root->data), count);

  // Right
  printBSTInOrder(root->child[2]);
}

// In order traversal means SELF, LEFT, RIGHT
void printBSTPreOrder(NaryNode *root)
{
  unsigned int count = 0;
  NaryNode *probe = root;

  // Terminating condition
  if (root == NULL)
    return;

  // Self
  while (probe)
  {
    count++;
    probe = probe->child[1];
  }
  printf("[%d (%d)]\n", *(int*)(root->data), count);

  // Left
  printBSTPreOrder(root->child[0]);

  // Right
  printBSTPreOrder(root->child[2]);
}
