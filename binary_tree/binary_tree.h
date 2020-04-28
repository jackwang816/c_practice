#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

typedef struct _node
{
    int data;
    struct _node * leftChild;
    struct _node * rightChild;
} Node, *pNode;

int pushLeft(pNode parent, int data);

#endif /* _BINARY_TREE_H */
