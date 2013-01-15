#ifndef NARYTREE_H
#define NARYTREE_H

// Data types
/**
 * This type is used for NaryNode.  It defines what type will be
 * used inside the data structure.
 */
typedef void* Data;

/**
 * This type is used for functions which are able to free a given
 * Data in an NaryNode object.
 */
typedef void (*DataFreeFunc)(Data);

/**
 * This type is used for functions which are able to print the
 * Data in an NaryNode object.
 */
typedef void (*DataPrintFunc)(Data);

/**
 * Data structure node for an N-ary tree.
 * An N-ary tree is a tree where each child can have
 * N children.  In some instances, all children will
 * have only N children, sometimes up to N children,
 * sometimes the number of children is unbound. This
 * data structure can handle all of these cases, it
 * is up to the code using it to define usage.
 */
typedef struct _narynode {
  Data data;                 ///< The data stored in the node
  unsigned int n;            ///< The number of children in <b>this</b> node
  struct _narynode **child;  ///< The child array (n children)
} NaryNode;

// General NaryNode functions
/**
 * Allocate and initialize an NaryNode in memory and return
 * a pointer to it.
 * \param data     The data to put in the created node
 * \param children The number of children to pre-allocate
 * \return A pointer to a newly allocated NaryNode
 */
NaryNode *createNaryNode(Data data, unsigned int children);

/**
 * Append the given node after the end of the child array
 * of the root node.  After this, the degree (n) of the node
 * will have been increased by one and the child array will
 * have been reallocated.
 * \param root    The node to whose child array newNode is to be added
 * \param newNode The node to be appended to root's child array
 */
void      appendChild(NaryNode *root, NaryNode *newNode);

/**
 * This function will expand the child array, inserting newNode as
 * the child at index asIndex.  If asIndex is past the end of the
 * child array, the child array will have NULLs appended until the
 * size is large enough to accomodate newNode.
 * \param root    The node to whose child array newNode is to be added
 * \param asIndex The index that the node will have in the child array
 * \param newNode The node to be appended to root's child array
 */
void      insertChild(NaryNode *root, unsigned asIndex, NaryNode *newNode);

/**
 * Count the number of nodes in the tree
 */
unsigned  sizeOfNaryTree(NaryNode *root);

/**
 * Free the subtree rooted at the given node.  If the free
 * function given is NULL, the data is not freed.
 * \param root The root of the subtree to free
 * \param free The function used to free the data in each node
 */
void      freeNaryTree(NaryNode *root, DataFreeFunc free);

/**
 * Print (in level order) the Nary tree given.  The print
 * function must not be null.
 * \param root  The subtree to print
 * \param print The function to use to print out data (should not print newline)
 */
void      printNaryTree(NaryNode *root, DataPrintFunc print);

/**
 * Utility methods for creating basic data types: int*
 */
Data      createIntData(int i);

/**
 * Utility methods for printing basic data types: int*
 */
void      printIntData(Data data);

#endif
