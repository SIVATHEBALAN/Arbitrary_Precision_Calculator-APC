#ifndef APC            // Header guard start
#define APC            // Define APC to prevent multiple inclusion

#define SUCCESS 0      // Success status code
#define FAILURE 1      // Failure status code

typedef struct operation   // Doubly linked list node structure
{
    int data;              // Data stored in the node
    struct operation *prev; // Pointer to previous node
    struct operation *next; // Pointer to next node
} op;

int insert_first(op **head, op **tail, int data);          // Insert a node at the beginning
int string_to_int(char digit);                             // Convert char digit to integer
void remove_leading_zeros(op **head, op **tail);           // Remove leading zeros from list
void print_list(op *head);                                 // Print the list contents
void add_numbers(op *, op *, op **op_head,op **op_tail);   // Add two numbers represented as lists
void swap_lists(op **head1, op **tail1, op **head2, op **tail2); // Swap contents of two lists
int compare_lists(op *head1, op *head2);                   // Compare two lists numerically
void sub_numbers(op *num1_head, op *num2_head, op **op_head, op **op_tail); // Subtract lists
int division(op *head1,op *head2,op **op_head,op **op_tail); // Divide two numbers (lists)
void multiply_numbers(op *num1, op *num2, op **op_head, op **op_tail); // Multiply numbers
void delete_list(op **head, op **tail);                    // Delete entire list
void insert_last(op **head, op **tail, int value);         // Insert node at the end

#endif   // End of header guard
