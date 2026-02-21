#include <stdio.h>
#include "Apc.h"
#include <stdlib.h>

int string_to_int(char ch)
{
    return ch - '0';     // Convert character digit to integer
}

int insert_first(op **head, op **tail, int data)
{
    op *new = malloc(sizeof(op));   // Allocate memory for new node
    if (new == NULL)
        return FAILURE;

    new->data = data;               // Store digit
    new->prev = NULL;               // New node has no previous
    new->next = *head;              // Next points to old head

    if (*head == NULL && *tail == NULL)   // If list is empty
    {
        *head = *tail = new;        // New node becomes head & tail
        return SUCCESS;
    }
    else
    {
        (*head)->prev = new;        // Update old head's prev
        *head = new;                // Set new node as head
        return SUCCESS;
    }
}

void remove_leading_zeros(op **head, op **tail)
{
    op *temp = *head;               // Start from head

    while (temp && temp->data == 0 && temp->next != NULL)
    {
        temp = temp->next;          // Move to next node
        free(temp->prev);           // Free previous zero node
        temp->prev = NULL;          // Update prev pointer
    }

    *head = temp;                   // Update head to first non-zero node
}

void print_list(op *head)
{
    if (head == NULL)
    {
        printf("INFO : List is empty\n");  // Empty list message
        return;
    }

    while (head)                  // Traverse and print each digit
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");                // Newline after printing number
}

void swap_lists(op **head1, op **tail1, op **head2, op **tail2)
{
    op *temp_h = *head1;          // Swap heads
    *head1 = *head2;
    *head2 = temp_h;

    op *temp_t = *tail1;          // Swap tails
    *tail1 = *tail2;
    *tail2 = temp_t;
}

int compare_lists(op *head1, op *head2)
{
    int len1 = 0, len2 = 0;        // Variables for lengths
    op *t1 = head1;
    op *t2 = head2;

    while (t1) { len1++; t1 = t1->next; }   // Count length of list 1
    while (t2) { len2++; t2 = t2->next; }   // Count length of list 2

    if (len1 > len2) return 1;              // Longer number is bigger
    if (len1 < len2) return -1;

    t1 = head1;                             // Reset pointers
    t2 = head2;

    while (t1 && t2)                        // Compare digit by digit
    {
        if (t1->data > t2->data) return 1;
        if (t1->data < t2->data) return -1;

        t1 = t1->next;
        t2 = t2->next;
    }

    return 0;                                // Numbers are equal
}

void delete_list(op **head, op **tail)
{
    if (head == NULL || *head == NULL)
        return;                              // Nothing to delete

    op *current = *head;
    op *next_node;

    while (current)                          // Free all nodes
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    *head = NULL;                            // List is now empty
    *tail = NULL;
}

void insert_last(op **head, op **tail, int value)
{
    op *new_node = (op *)malloc(sizeof(op));  // Allocate new node
    if (!new_node)
    {
        printf("Memory allocation failed\n"); // Allocation failure
        return;
    }

    new_node->data = value;                  // Store digit
    new_node->next = NULL;                   // Last node → next NULL
    new_node->prev = NULL;

    if (*head == NULL)                       // If list is empty
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        new_node->prev = *tail;              // Link with old tail
        (*tail)->next = new_node;
        *tail = new_node;                    // Update tail
    }
}
