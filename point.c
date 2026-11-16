#include <stdio.h>
#include <cs50.h>

float avr ( int l , int a[]);

int num = 1;

int main (void)
{
    printf("\n<<<<<<<<<< AVREGE CALC >>>>>>>>>>\n");
    printf("FOR : [Exit : 0 || Help : 1 ]\n");
    do
    {
        int num = get_int("\nHow many : ");
        if (num == 0)
        {
            printf("\nEXIT COMPLETED !!!   \n");
            printf(",,,,,,,,,,,,,,,,,,,,,\n");
            printf("| THANK YOU FOR USE |\n");
            printf("| MADE BY RASHADOOZ |\n");
            printf("`````````````````````\n");
            break;
        }

        else if (num == 1)
        {
            printf("\nHow many : num of things you will input\nnum (n)  : the input\n\n");
        }
        
        int nums[num];
        for (int i = 0; i < num; i++)
        {
               nums[i] = get_int("num %i :", i+1 );    
        }
        printf("the result :%.3f\n" , avr(num ,nums));
    }
    while (num != 0 || num != 1);
}
//the avrege function 
float avr ( int l , int a[])
{
    int total = 0;
    for (int i = 0; i < l; i++)
    {
        total += a[i];
    }
    return total /(float) l ;
}
