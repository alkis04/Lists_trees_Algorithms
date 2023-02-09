//NOT IMPORTANT 
//WORK IN PROGRESS

#include <stdio.h>
#include <stdlib.h>

struct treenode
{
    int data;
    struct treenode *left;
    struct treenode *right;
};

typedef struct treenode *Treeptr;

Treeptr non_recursive_addtree(Treeptr tree, int d)
{
    Treeptr new_node = malloc(sizeof(struct treenode));
    new_node->data = d;
    new_node->right = NULL;
    new_node->left = NULL;
    
    if(tree == NULL)
    {
        tree = new_node;
    }
    else
    {
        Treeptr current = tree;
        Treeptr parent = NULL;
        while(current != NULL)
        {
            parent = current;
            if(d > current->data)
            {
                current = current->right;
            }else if(d < current->data)
            {
                current = current->left;
            }
        }
        if(d > parent->data)
        {
            parent->right = new_node;
        }else if(d < parent->data)
        {
            parent->left = new_node;
        }
    }
    return tree;
}

void non_recursive_print_tree(Treeptr tree)
{
    Treeptr stack[100];
    int top = 0;
    while(tree != NULL)
    {
        stack[top++] = tree;
        tree = tree->left;
    }
    while(top > 0)
    {
        tree = stack[--top];
        printf("%d ", tree->data);
        tree = tree->right;
        while(tree != NULL)
        {
            stack[top++] = tree;
            tree = tree->left;
        }
    } 
}