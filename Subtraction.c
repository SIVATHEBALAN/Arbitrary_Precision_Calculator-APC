#include"Apc.h"              // include APC header file
#include<stdio.h>            // include standard I/O functions

void sub_numbers(op *num1_head, op *num2_head, op **op_head, op **op_tail)
{
    int borrow = 0;          // variable to track borrow during subtraction

    op *temp1 = num1_head;   // pointer to traverse first number
    op *temp2 = num2_head;   // pointer to traverse second number

    while (temp1 && temp1->next)   // move temp1 to last digit
        temp1 = temp1->next;       // traverse towards tail
    while (temp2 && temp2->next)   // move temp2 to last digit
        temp2 = temp2->next;       // traverse towards tail

    while (temp1 != NULL || temp2 != NULL )   // subtract until both lists end
    {
        int d1, d2;          // variables for digit values

        if (temp1 != NULL)   // if num1 node exists
            d1 = temp1->data; // store its digit
        else
            d1 = 0;          // otherwise treat as zero

        if (temp2 != NULL)   // if num2 node exists
            d2 = temp2->data; // store its digit
        else
            d2 = 0;          // otherwise treat as zero

        int sub = 0;         // variable to store final digit result

        d1 = d1 - borrow;    // apply previous borrow to current digit

        if (d1 < d2)         // if borrow is needed
        {
            borrow = 1;      // set borrow for next step
            d1 = d1 + 10;    // add 10 to enable subtraction
        }    
        else
        {
            borrow = 0;      // no borrow required
        }

        sub = d1 - d2;       // compute the difference between digits

        insert_first(op_head, op_tail, sub);  // insert result digit at front

        if (temp1)           // move to previous digit in num1
           temp1 = temp1->prev;
        if (temp2)           // move to previous digit in num2
           temp2 = temp2->prev;
    }
}
