#include"Apc.h"
#include<stdio.h>

void add_numbers(op *num1_head, op *num2_head, op **op_head, op **op_tail)
{
    int carry = 0;                       // Carry value for addition

    op *temp1 = num1_head;               // Pointer to traverse first number
    op *temp2 = num2_head;               // Pointer to traverse second number

    while (temp1 && temp1->next)         // Move to last digit of num1
        temp1 = temp1->next;
    while (temp2 && temp2->next)         // Move to last digit of num2
        temp2 = temp2->next;

    delete_list(op_head, op_tail);       // Clear old result list

    while (temp1 != NULL || temp2 != NULL)   // Continue until both lists are done
    {
        int d1 = (temp1) ? temp1->data : 0;   // Get digit from num1 or 0
        int d2 = (temp2) ? temp2->data : 0;   // Get digit from num2 or 0

        int sum = d1 + d2 + carry;            // Calculate sum of digits + carry
        carry = sum / 10;                     // Compute new carry
        sum = sum % 10;                       // Extract last digit

        insert_first(op_head, op_tail, sum);  // Insert sum digit into result

        if (temp1) temp1 = temp1->prev;       // Move backward in num1
        if (temp2) temp2 = temp2->prev;       // Move backward in num2
    }

    if (carry > 0)                             // Insert remaining carry if exists
        insert_first(op_head, op_tail, carry);
}
