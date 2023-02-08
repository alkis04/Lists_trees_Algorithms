#include <stdio.h>
#include <stdlib.h>

struct treenode
{
    int data;
    struct treenode *left;
    struct treenode *right;
};

typedef struct treenode *Treeptr;

Treeptr addtree(Treeptr tree, int d)
{
    if(tree == NULL)
    {
        Treeptr new_node = malloc(sizeof(struct treenode));
        new_node->data = d;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    else if(d > tree->data)
    {

    }
}

int main()
{


    return 0;
}