#include <stdio.h>            // Standard I/O library
#include <stdlib.h>           // Standard library for memory functions
#include <string.h>           // String functions
#include "Apc.h"              // Custom header file

int main(int argc, char *argv[])
{
    if (argc != 4)            // Check correct number of arguments
    {
        // printf("Usage: ./a.out <num1> <op> <num2>\n");
        printf("Invalid arguments\nFormate: ./a.out <num1> <op> <num2>\n");
        return FAILURE;       // Exit if arguments incorrect
    }

    
    op *head1 = NULL, *tail1 = NULL;
    op *head2 = NULL, *tail2 = NULL;
    op *op_head = NULL, *op_tail = NULL;

    char *num1 = argv[1];     // First number (string input)
    char *op = argv[2];       // Operator (+, -, x, /)
    char *num2 = argv[3];     // Second number (string input)

    int len1 = strlen(num1);  // Length of num1
    int len2 = strlen(num2);  // Length of num2

    int sign1, sign2;         // Signs of numbers
    int start1, start2;       // Index to start after detecting sign

   
    if (num1[0] == '-')       // Negative number
    {
        sign1 = -1;
        start1 = 1;           // Skip '-' sign
    }
    else if (num1[0] == '+')  // Explicit positive sign
    {
        sign1 = 1;
        start1 = 1;
    }
    else                      // No sign → positive
    {
        sign1 = 1;
        start1 = 0;
    }

   
    if (num2[0] == '-')       // Negative number
    {
        sign2 = -1;
        start2 = 1;           // Skip '-' sign
    }
    else if (num2[0] == '+')  // Explicit positive sign
    {
        sign2 = 1;
        start2 = 1;
    }
    else                      // No sign → positive
    {
        sign2 = 1;
        start2 = 0;
    }

    
    for (int i = len1 - 1; i >= start1; i--)   // Traverse from last digit
    {
        int d = string_to_int(num1[i]);        // Convert char to number
        insert_first(&head1, &tail1, d);       // Insert digit into list
    }

 
    for (int i = len2 - 1; i >= start2; i--)   // Traverse from last digit
    {
        int d = string_to_int(num2[i]);        // Convert char to number
        insert_first(&head2, &tail2, d);       // Insert digit into list
    }

    int negative = 0;          // final sign of result

   
    switch (op[0])             // Check which operator is given
    {
        case '+':              // Addition case
        {
            if (sign1 == sign2)   // Same signs → simple addition
            {
                add_numbers(head1, head2, &op_head, &op_tail);
                negative = (sign1 == -1);      // Result negative if both negative
            }
            else                    // Signs differ → perform subtraction
            {
                int cmp = compare_lists(head1, head2);   // Compare magnitudes

                if (cmp == 0)        // Both numbers equal
                {
                    insert_first(&op_head, &op_tail, 0); // Result = 0
                    negative = 0;
                }
                else if (cmp > 0)    // num1 > num2
                {
                    sub_numbers(head1, head2, &op_head, &op_tail);
                    negative = (sign1 == -1);
                }
                else                 // num2 > num1
                {
                    swap_lists(&head1, &tail1, &head2, &tail2); // Swap to subtract correctly
                    sub_numbers(head1, head2, &op_head, &op_tail);
                    negative = (sign2 == -1);
                }
            }
            break;
        }

        case '-':               // Subtraction case
        {
            // a - b = a + (-b)
            sign2 = -sign2;     // Flip sign of second number

            if (sign1 == sign2)   // Same sign after flipping → addition
            {
                add_numbers(head1, head2, &op_head, &op_tail);
                negative = (sign1 == -1);
            }
            else                 // Otherwise subtraction
            {
                int cmp = compare_lists(head1, head2);

                if (cmp == 0)    // Equal numbers
                {
                    insert_first(&op_head, &op_tail, 0); // Result = 0
                    negative = 0;
                }
                else if (cmp > 0) // num1 > num2
                {
                    sub_numbers(head1, head2, &op_head, &op_tail);
                    negative = (sign1 == -1);
                }
                else              // num2 > num1
                {
                    swap_lists(&head1, &tail1, &head2, &tail2); // Swap to subtract safely
                    sub_numbers(head1, head2, &op_head, &op_tail);
                    negative = (sign2 == -1);
                }
            }
            break;
        }

        case 'x':               // Multiplication symbol
        case 'X':
        case '*':
            multiply_numbers(head1, head2, &op_head, &op_tail); // Perform multiplication
            negative = (sign1 != sign2);       // If signs differ → negative result
            break;

        case '/':               // Division operator
            if(division(head1, head2, &op_head, &op_tail)==SUCCESS) // Perform division
                negative = (sign1 != sign2);  // Determine final sign
            break;

        default:                // Invalid operator entered
            printf("Invalid operator\n");
            return FAILURE;
    }

   
    printf("First Number    : ");
    print_list(head1);          // Print first number

    printf("Second Number   : ");
    print_list(head2);          // Print second number
    printf("Result          : ");
    if (negative)               // Print minus sign if needed
        printf("-");

    remove_leading_zeros(&op_head, &op_tail);   // Clean up result list
    print_list(op_head);       // Print final result

    return SUCCESS;            // End of program
}
