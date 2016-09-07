#include <stdio.h>
#include <stdlib.h>

struct Node { int number;  struct Node * next; };

int main()
{
    struct Node * head = NULL;
    struct Node * tail = NULL;
    // Read numbers from stdin and store them in the list
    while (!feof(stdin)) {
        int x;
        scanf("%d", &x);
        // Create a new node to hold value of x
        struct Node * node = (struct Node *) malloc(sizeof(struct Node));
        node->number = x;
        node->next = NULL;
        // Add the new node to the end of the list
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    // Calculate sum and product
    int sum = 0;
    int product = 1;
    struct Node * iter = head;
    while (iter) {
        product *= iter->number;
        sum += iter->number;
        iter = iter->next;
    }
    printf("Sum = %d, Product = %d\n", sum, product);
    // Free the list
    iter = head;
    while (iter) {
        free(iter);
        iter = iter->next;
    }
    return 0;
}
