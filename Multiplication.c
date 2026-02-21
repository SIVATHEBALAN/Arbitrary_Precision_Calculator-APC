#include"Apc.h"        // include header file for APC functions
#include<stdio.h>      // include standard I/O library

void multiply_numbers(op *head1, op *head2, op **op_head, op **op_tail)
{
    op *res1_head = NULL;   // final result head pointer
    op *res1_tail = NULL;   // final result tail pointer
    
    op *temp2 = head2;      // pointer to traverse second number
    int shift_count = 0;    // number of zeros for positional shift

    while (temp2 && temp2->next)   // move to last digit of second number
        temp2 = temp2->next;       // traverse to next node

    while (temp2)                  // iterate through num2 from right to left
    {
        op *res2_head = NULL;      // head of partial product
        op *res2_tail = NULL;      // tail of partial product
        op *temp1 = head1;         // pointer to traverse first number

        while (temp1 && temp1->next)   // move to last digit of first number
            temp1 = temp1->next;       // traverse to next node

        int carry = 0;             // carry for multiplication

        while (temp1)              // multiply digits of num1 with current digit of num2
        {
            int prod = temp1->data * temp2->data + carry; // compute product + carry
            carry = prod / 10;                             // update carry
            int digit = prod % 10;                         // extract digit

            insert_first(&res2_head, &res2_tail, digit);   // insert digit at front of list

            temp1 = temp1->prev;                           // move left in num1
        }

        if (carry > 0)                                     // if any carry remains
            insert_first(&res2_head, &res2_tail, carry);   // insert carry at front

        for (int i = 0; i < shift_count; i++)              // append shift_count zeros
            insert_last(&res2_head, &res2_tail, 0);        // insert zero at end

        if (!res1_head)                                    // if first partial product
        {
            res1_head = res2_head;                         // store as initial result
            res1_tail = res2_tail;                         // update tail pointer
        }
        else                                               // otherwise add to existing result
        {
            op *res3_head = NULL;                          // head for sum list
            op *res3_tail = NULL;                          // tail for sum list

            add_numbers(res1_head, res2_head, &res3_head, &res3_tail); // add partial product to cumulative result

            delete_list(&res1_head, &res1_tail);           // delete old result list
            delete_list(&res2_head, &res2_tail);           // delete partial product list

            res1_head = res3_head;                         // update final result head
            res1_tail = res3_tail;                         // update final result tail
        }

        shift_count++;                                     // increase positional shift
        temp2 = temp2->prev;                               // move to previous digit of num2
    }

    *op_head = res1_head;                                  // set output head pointer
    *op_tail = res1_tail;                                  // set output tail pointer
}
