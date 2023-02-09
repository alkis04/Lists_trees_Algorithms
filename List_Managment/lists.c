#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listnode *Listptr;

struct listnode
{
    int data;
    Listptr next;
};


//function that checks if a list is empty
int empty(Listptr list)
{
    if(list == NULL) return 1; //Yes, it is empty
    else return 0; //No, it isn't
}

//Function that frees the memory of a list
void free_list(Listptr *list)
{
    Listptr current = *list;
    Listptr next;
    while(current != NULL) /*Visit elements up to end*/
    {
        next = current->next; /*Update the next pointer*/
        free(current); /*Free the current node*/
        current = next; /*Go to the next item*/
    }

    *list = NULL; /*Change the list pointer to NULL (by reference)*/
}

//function that checks if a value exist on the list
int search_for(Listptr list, int value)
{
    while(list != NULL) /*Visit elements up to end*/
    {
        if(list->data == value)
            return 1; /*Value found*/
        else 
            list = list->next; /*Continue with the next element*/
    }
    return 0; /*Value not found*/
}

//function that inserts a new element at the beginning 
void insert_at_start(Listptr *list, int d)
{
    Listptr new_node = malloc(sizeof(struct listnode)); /*Create a new node*/
    new_node->next = (*list); /*Make the next element of the new node, the previous first item of the list*/
    new_node->data = d; /*Store value d*/
    (*list) = new_node; /*Make the *list pointer to point at the new node (the new start of the list)*/
}


//function that inserts a new element before the nth element of the list
//or at the end of the list 
int insert_at_n(Listptr *list, int n, int d)
{
    if(n == 0) /*Same as insert_at_start*/
    {
        insert_at_start(list, d);
        return 1;
    }
    int i = 0;
    Listptr current = *list;
    Listptr prev = NULL;
    while(current != NULL && i < n)
    {
        prev = current;
        current = current->next;
        i++;
    }
    if(i == n) /*We found the nth element*/
    /*Even if the nth elemnt doesnt exist and current = NULL*/
    /*insert at start will create a new node that points to NULL, which is a valid last element*/
    {
        insert_at_start(&current, d); /*We insert a new node as if the list starts from current*/
        prev->next = current; /*We connect the rest of the list*/
        return 1;
    }
    else
        return 0; 
}

//Function that deletes the first node of the list with value = v
int delete_v(Listptr *list, int v)
{
    if(empty(*list)) return 0;

    Listptr current = *list, prev = NULL;

    while(current->data != v && current != NULL) /*Visit elements till we find v or up to end*/
    {
        prev = current; /*Update the previous pointer node*/
        current = current->next; /*Update the current pointer node*/
    }
    if(current == NULL) /*The value v doesnt exist in the list*/
        return 0;
    if(prev == NULL) /*The value v is in the first node of the list*/
    {
        *list = current->next; /*Move the list pointer to the next node*/
    }
    else 
    {
        prev->next = current->next; /*Change the next pointer of the previous note to skip the current node*/
    }
    free(current); /*Free the current node*/
    return 1;
}

/*Removes the first node of the list*/    
int pop_front(Listptr *list)
{
    if(empty(*list))
        return 0;
    Listptr to_free = *list; /*Save the pointer of the first node*/
    *list = (*list)->next; //NOT *(list) /*Move the pointer to the next element (by reference)/*
    free(to_free); /*Free the first node*/
    return 1;
}

//Function that removes the last node of the list
int pop_back(Listptr *list)
{
    if(empty(*list))
        return 0;
    Listptr current = *list;
    Listptr prev = NULL;
    while(current->next != NULL) /*Go to the last node of the list*/
    {
        prev = current;
        current = current->next;
    }
    if(prev == NULL) /*If the last node is also the first node*/
    {
        *list = NULL; /*Now list is empty*/
    }
    else
        prev->next = NULL; /*Skip the current node*/

    free(current); /*Free the current node*/
    return 1;
}

//Function that deletes the nth element of the list
int delete_nth_element(Listptr *list, int n)
{
    if(*list == NULL || n < 0) return 0;
    if(n == 0) /*Same as pop_front*/
    {
        return pop_front(list);
    }
    int i = 0;
    Listptr current = *list, prev = NULL;
    while(current != NULL && i < n) /*Go to the nth item of the list if this exist*/
    {
        prev = current;
        current = current->next;
        i++;
    }
    if(current == NULL) /*The nth of the list doesn't exist*/
    {
        return 0;
    }
    else
    {
        if(prev == NULL) /*The nth item of the list is the first item of the list*/
        {
            *list =current->next; /*Change the *list pointer to point at the second node*/
        }
        else
        {
            prev->next = current->next; /*Skip the current node*/
        }
        free(current); /*Free the current node*/
        return 1;
    }
}

//Function that adds a node at the end of a list
void insert_at_end(Listptr list, int d)
{
    Listptr current = list;
    while(current->next != NULL) /*Go to the end of the list*/
    {
        current = current->next;
    }
    Listptr new_node = malloc(sizeof(struct listnode)); /*Make a new node*/
    new_node->data = d; /*Store the value*/
    new_node->next = NULL; /*Make the new node point to NULL, as the last item of any list should*/
    current->next = new_node; /*Connect the previous last node to the new last node*/
}

//Function that prints the values stored in a list
void print_list(Listptr list)
{
    Listptr current = list; /*We use current to go through the list*/
    while(current != NULL) /*Visit the elements up to end*/
    {
        printf("%d ", current->data); /*Print the value*/
        current = current->next; /*Go to the next node*/
    }
    printf("\n");

}

//Funnction that returns the nth element of the list
int nth_element(Listptr list, int n, int *nth)
{
    if(list == NULL || n < 0) return 0;
    int i = 0;
    Listptr current = list;
    while(current != NULL && i < n) /*Go to the nth item of the list if this exist*/
    {
        current = current->next;
        i++;
    }
    if(current == NULL) /*The nth of the list doesn't exist*/
    {
        return 0;
    }
    else
    {
        *nth = current->data; /*Pass the value of the nth item of the list*/
        return 1;
    }
}

//Function that returns the number of elements of the list
int list_size(Listptr list)
{
    int size = 0;
    Listptr current = list;
    while(current != NULL) /*Visit the elements up to end*/
    {
        size++; /*Increase the size*/
        current = current->next; /*Go to the next node*/
    }
    return size;
}

int main(void)
{
    Listptr list = NULL;
    //case that gives access to every function with commands from stdin
    char command[50];
    int n, d;
    while(scanf("%s", command) != EOF)
    {
        if(strcmp(command, "inserts") == 0)
        {
            scanf("%d", &d);
            insert_at_start(&list, d);
        }
        else if(strcmp(command, "inserte") == 0)
        {
            scanf("%d", &d);
            insert_at_end(list, d);
        }
        else if(strcmp(command, "insertn") == 0)
        {
            scanf("%d %d", &n, &d);
            if(!insert_at_n(&list, n, d))
                printf("Failed\n");
        }
        else if(strcmp(command, "deleten") == 0)
        {
            scanf("%d", &n);
            delete_nth_element(&list, n);
        }
        else if(strcmp(command, "deletev") == 0)
        {
            scanf("%d", &d);
            if(delete_v(&list, d) == 0)
                printf("Failed\n");
        }
        else if(strcmp(command, "popf") == 0)
        {
            pop_front(&list);
        }
        else if(strcmp(command, "popb") == 0)
        {
            pop_back(&list);
        }
        else if(strcmp(command, "search") == 0)
        {
            scanf("%d", &n);
            if(search_for(list, n))
                printf("Found\n");
            else
                printf("Not found\n");
        }     
        else if(strcmp(command, "print") == 0)
        {
            print_list(list);
        }
        else if(strcmp(command, "nth") == 0)
        {
            scanf("%d", &n);
            int nth;
            if(nth_element(list, n, &nth))

            printf("%d\n", nth);
            else
                printf("Failed\n");
            
        }
        else if(strcmp(command, "size") == 0)
        {
            printf("%d\n", list_size(list));
        }
        else if(strcmp(command, "empty") == 0)
        {
            if(empty(list))
                printf("Empty\n");
            else
                printf("Not empty\n");
        }
        else if(strcmp(command, "free") == 0)
        {
            free_list(&list);
        }
        else if(strcmp(command, "exit") == 0)
        {
            free_list(&list);
            break;
        }
        else
        {
            printf("Invalid command\n");
        }       
    }   
    return 0;
}