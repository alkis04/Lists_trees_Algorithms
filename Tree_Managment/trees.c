#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x,y) (x) > (y) ? (x) : (y)

struct treenode
{
    int data;
    struct treenode *left;
    struct treenode *right;
};

typedef struct treenode *Treeptr;

        /*BASIC TREE MANAGMENT FUNCTIONS*/

//Function that adds a node to a binary search tree
Treeptr addtree(Treeptr tree, int d)
{
    if(tree == NULL) /*If subtree is empty*/
    {
        tree = malloc(sizeof(struct treenode)); /*Allocate space for new node*/
        tree->data = d; /*Store data*/
        tree->right = NULL; /*Initialize right to NULL*/
        tree->left = NULL; /*Initilize left to NULL*/
    }
    else if(d > tree->data) /*If d is bigger than current node*/
    {
        tree->right = addtree(tree->right, d); /*Insert it into the right subtree*/
    }else if(d < tree->data) /*If d is smaller than current node*/
    {
        tree->left = addtree(tree->left, d); /*Insert it into the left subtree*/
    }
    /*If d is equal to an existing node, do not insert it*/
    return tree;
}

//Function that prints tree nodes in increasing order (sorted)
void print_tree(Treeptr tree)
{
    if(tree == NULL) return;
   
    
    print_tree(tree->left); /*Print left subtree*/
    printf("%d ", tree->data); /*Print root node*/
    print_tree(tree->right); /*Print right subtree*/
    
}

//Function that calculates the depth of a tree
int tree_depth(Treeptr tree)
{
    if(tree == NULL) return 0; /*If tree is empty depth is 0*/

    int depth_l, depth_r;

    depth_l = tree_depth(tree->left); /*Find the depth of the left subtree*/
    depth_r = tree_depth(tree->right); /*Find the depth of the right subtree*/

    return max(depth_l, depth_r) + 1; /*The depth of the tree is the max of depths PLUS ONE!*/
}

//Function that checks if a value exist in a tree
int treesearch(Treeptr tree, int value)
{
    if(tree == NULL) /*Value doesn't exist in the tree (or the subtree)*/
        return 0;
    
    if(value > tree->data) /*If value is bigger than current data*/
    {
        return treesearch(tree->right, value); /*Search for value in the right subtree*/
    }
    else if(value < tree->data) /*If value is smaller*/
    {
        return treesearch(tree->left, value); /*Search for value in the left subtree*/
    }
    else /*If value is equal*/
        return 1; /*We found the value in the tree*/
}

//Function that frees the tree
void free_tree(Treeptr tree)
{
    //We need to free the subtrees first before we free the root
    if(tree == NULL) return;
    free_tree(tree->left); /*Free the left subtree*/
    free_tree(tree->right); /*Free the right subtree*/
    free(tree); /*Free the root*/
} //Remember to the tree to NULL after freeing

        /*ADVANCED FUNCTION*/

//Function that deletes a value from a binary search tree
Treeptr delete_v(Treeptr tree, int value)
{
    if(tree == NULL) return NULL; /*Tree is empty*/
    
    /*Search for the node with the value*/
    if(value > tree->data) 
    {
        tree->right = delete_v(tree->right, value); /*Search in the right subtree*/
    }
    else if(value < tree->data)
    {
        tree->left = delete_v(tree->left, value); /*Search in the left subtree*/
    }
    else /*We found the node that should be deleted*/
    {
        //Case 1: The node is a leaf node
        if(tree->left == NULL && tree->right == NULL)
        {
            free(tree); /*We can just delete the node*/
            return NULL; /*And return NULL*/
        }
        //Case 2: a)The node has one right child
        else if(tree->left == NULL)
        {
            Treeptr temp = tree->right; /*Bypass the node that we should delete*/
            free(tree); /*Free the node that we should delete*/
            return temp; /*Return the new right branch*/
        }
        //        b)The node has one left child             
        else if(tree->right == NULL)
        {
            Treeptr temp = tree->left; /*Bypass the node that we should delete*/
            free(tree); /*Free the node that we should delete*/
            return temp; /*Return the new left branch*/
        }
        //Case 3: The node has two childs
        else
        {
            Treeptr temp = tree->right; /*Go to the right subtree*/
            while(temp->left != NULL) /*Find the smallest node in the subtree (souldn't have a left child)*/
            {
                temp = temp->left; /*Go all the way left to find the smallest node in the subtree*/
            }
            tree->data = temp->data; /*Copy the smallest node to the tree*/
            tree->right = delete_v(tree->right, temp->data); /*Delete the duplicated node*/
            /*Because we copied the smallest node in the from the right branch the binary search tree should maintain its structure*/
            /*https://youtu.be/gcULXE7ViZw for detailed explanation*/
        }
    }
    return tree;
}

int main(void)
{
    Treeptr tree = NULL;
    //case that gives access to all the functions via commands in the console
    char command[50];
    int data;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "add") == 0)
        {
            scanf("%d", &data);
            tree = addtree(tree, data);
        }
        else if(strcmp(command, "print") == 0)
        {  
            if(tree == NULL)
            {
                printf("NULL\n");
                continue;
            }
            print_tree(tree);
            printf("\n");
        }
        else if(strcmp(command, "search") == 0)
        {
            scanf("%d", &data);
            if(treesearch(tree, data))
            {
                printf("Found %d\n", data);
            }
            else
            {
                printf("Not found %d\n", data);
            }
        }
        else if(strcmp(command, "depth") == 0)
        {
            printf("Depth: %d\n", tree_depth(tree));
        }
        else if(strcmp(command, "delete") == 0)
        {
            scanf("%d", &data);
            tree = delete_v(tree, data);
        }
        else if (strcmp(command, "free") == 0)
        {
            free_tree(tree);
            tree = NULL;
        }
        
        else if(strcmp(command, "exit") == 0)
        {
            free_tree(tree);
            break;
        }
        else 
        {
            printf("Invalid command\n");
        }
    }



    return 0;
}