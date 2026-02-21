#include"Apc.h"
#include<stdio.h>

int division(op *head1, op *head2, op **op_head, op **op_tail)
{
    if (!head2 || (head2->data == 0 && !head2->next))
    {
        printf("Division by zero is not allowed\n");     // Cannot divide by zero
        insert_first(op_head, op_tail, 0);        // Return 0 for invalid division
        return FAILURE;                           // Indicate failure result
    }

    op *temp_h = NULL, *temp_t = NULL;            // Temporary accumulator for repeated addition
    insert_first(&temp_h, &temp_t, 0);            // Initialize accumulator to zero

    op *count_h = NULL, *count_t = NULL;          // Counter to store final quotient
    insert_first(&count_h, &count_t, 0);          // Initialize quotient to zero

    op *one_h = NULL, *one_t = NULL;              // Represents constant digit '1'
    insert_first(&one_h, &one_t, 1);              // Used to increment count

    while (1)
    {
        op *new_temp_h = NULL, *new_temp_t = NULL;    // Stores temp + divisor
        add_numbers(temp_h, head2, &new_temp_h, &new_temp_t);  // Compute next accumulation

        if (compare_lists(new_temp_h, head1) == 1)     // Stop when accumulated > dividend
        {
            delete_list(&new_temp_h, &new_temp_t);     // Free unused list
            break;                                     // Exit loop
        }

        op *new_count_h = NULL, *new_count_t = NULL;   // Stores count + 1
        add_numbers(count_h, one_h, &new_count_h, &new_count_t); // Update quotient count

        delete_list(&temp_h, &temp_t);                 // Replace old temp with new value
        temp_h = new_temp_h;
        temp_t = new_temp_t;

        delete_list(&count_h, &count_t);               // Replace old count with new value
        count_h = new_count_h;
        count_t = new_count_t;
    }

    op *p = count_h;                                   // Pointer to copy quotient digits
    while (p)
    {
        insert_last(op_head, op_tail, p->data);        // Append result digit to output
        p = p->next;                                   // Move to next digit
    }

    return SUCCESS;                                    // Division completed successfully
}
