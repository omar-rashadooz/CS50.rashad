#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int x;
    int y;
    string z;
    z = get_string("the thing that you want to copy = ");
    do
    {
        x = get_int("num of x (that should be :1)    = ");
        y = get_int("num of y (enter what you want)  = ");
    } while (x<1 || y<1);
    
    
    for (int i = 0; i < y; i++)
    {
        for (int i = 0; i < x; i++)
        {
          printf("%s", z);
        }
        printf("\n");
    }   
}