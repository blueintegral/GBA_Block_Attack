#ifndef NARYBST_H
#define NARYBST_H

// N=3 Binary Search Tree Functions
#define N 3

/*
 * So, here's how this works.  In ASCII.
 * <pre>
 *           [DATA   N=3   CHILDREN]
 *                        /    |    \ 
 *                  {<Data} {=DATA} {>DATA}
 * </pre>
 * All children whose data is less than the node's data
 * end up in child[0], all children whose data is greater
 * end up in child[2], and all children whose data is equal
 * to the node end up in child[1]. If you're paying close
 * attention, this means that the middle subtree will
 * essentially be a linked list, and this simplification
 * is used in some of the following code.
 */

/**
 * Insert the given node into the BST implemented with an
 * NaryNode.  The convention used is discussed above.
 * <br/><br/>
 * Example:
 * <code>
 *   root = insertBSTNode(root, createNaryNode(newData, numChildren));
 * </code>
 *
 * \param root    The subtree into which to insert newNode
 * \param newNode The node to insert into root's subtree
 * \return A pointer to the root of the new subtree
 */
NaryNode *insertBSTNode(NaryNode *root, NaryNode *newNode);

/**
 * Print the tree (as a BST, see above) in order to
 * standard output.
 * \param root The root of the subtree to print
 */
void printBSTInOrder(NaryNode *tree);

/**
 * Print the tree (as a BST, see above) with a pre-order
 * traversal to the standard output.
 * \param root The root of the subtree to print
 */
void printBSTPreOrder(NaryNode *tree);

#endif
