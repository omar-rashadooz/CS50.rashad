#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <cs50.h>

string name;
void main (void)
{
    do
    {
        string name = get_string(">>");
    } while (name != "exit");
    
    

    if (name == "ls")
    {
        system("ls"); 
    }
    else if (name == "clear")
    {
        system("clear");
    }
    else if (name == "exit")
    {
        system("ctrl+C");
    }
    
}
    