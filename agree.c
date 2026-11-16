#include <stdio.h>
#include <cs50.h>

void stat(void);

int main(void)
{
    int s = get_int("enter loop num : ");
    for (int i=0; i<s; i++)
    {
        stat(); 
    }               
}

void stat(void)
{
    char s = get_char("Are you sure ?(y,n): ");
        if (s == 'y' || s =='Y')
        {
            printf("you are agree\n");
        }
        else if (s == 'n' || s == 'N')
        {
            printf("you are disagree\n");
        }
        else
            printf("worng answer.....\n");
}
