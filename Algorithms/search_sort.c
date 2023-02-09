#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
        /*TESTING FUNCTIONS*/
int *generate(int n)
{
    int limit = n * 10;
    int *arr = malloc(n * sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        arr[i] = rand() % limit;
    }
    return arr;
}
void print_arr(int *arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

        /*BASIC FUNCTIONS*/

void swap(int *a, int *b)
{
    int t = *b;
    *b = *a;
    *a = t;
}

void quicksort(int *arr, int left, int right)
{
    int i = left, j = right;

    /*We choose PIVOT to be the arr[left]*/
    /*After the following process pivot should be fully sorted*/
    /*Which means that every element smaller than pivot will be left*/
    /*and every element larger than pivot will be right*/
    while(i < j)
    {
        /*Let elements larger than pivot stay where they are*/
        while(arr[j] >= /*Pivot*/ arr[i] && i < j) j--;
        if(i != j) /*If pivot is not reached*/
        {
            swap(&arr[i], &arr[j]); /*exchange it with smaller element*/
            i++; /*Pivot is at j position*/
            /*We swapped arr[i] so we move one step right*/
        }

        /*Let elements smaller than pivot stay where they are*/
        while(arr[i] <= /*Pivot*/ arr[j] && i < j) i++;
        if(i != j) /*If pivot is not reached*/
        {
            swap(&arr[i], &arr[j]); /*exchange it with larger element*/
            j--; /*Pivot is at i position*/
            /*We swapped arr[j] so we move one step left*/
        }
    }
    /*Now pivot is in its correct position*/
    if (left < i-1) /*Is there at least one element left of pivot? */
        quicksort(arr, left, i-1); /* Quick(sort) smaller elements */
    if (right > j+1)/* Is there at least one element right of pivot? */
        quicksort(arr, j+1, right);  /* Quick(sort) larger elements */
}

void heap_sort(int *arr, int n)
{
   
}

void binary_search(int *arr, int n, int key)
{
    int left = 0, right = n - 1;
    int mid;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(arr[mid] == key)
        {
            printf("Found %d at index %d\n", key, mid);
            return;
        }
        else if(arr[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    printf("Not found\n");
}


int main(void)
{
    char command[50];
    int n = 0;
    int *arr = NULL;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "gen") == 0)
        {
            scanf("%d", &n);
            if(arr != NULL)
                free(arr);
            arr = generate(n);
        }
        else if(strcmp(command, "print") == 0)
        {
            print_arr(arr, n);
        }
        else if (strcmp(command, "hsort") == 0)
        {
            heap_sort(arr, n);
        }
        else if (strcmp(command, "sort") == 0)
        {
            quicksort(arr, 0, n - 1);
        }
        else if(strcmp(command, "search") == 0)
        {
            int key;
            scanf("%d", &key);
            binary_search(arr, n, key);
        }
        else if(strcmp(command, "exit") == 0)
        {
            free(arr);
            break;
        }
        else 
        {
            printf("Invalid command\n");
        }  
    }
    return 0;
}