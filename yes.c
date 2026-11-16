#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string("USER NAME   : ");
    string password;
    string repasswd;
    int l;
    // Use do-while loop to ensure password and repasswd are accepted
    do
    {
        password = get_string("PASSWORD    : ");
        repasswd = get_string("RE-PASSWORD : ");
        int l = strlen(password);

        // Check if passwords match, have the correct length, and are not the same
        if (strcmp(password, repasswd) == 0 && l >= 8 && l <= 16)
        {
            printf("SIGN UP COMPLETED MR %s !\n", name);
            break;
        }
        else
        {
            printf("Passwords match, but password length is out of range or passwords do not match. Please try again.\n");
        }
    } while (strcmp(password, repasswd) != 0 || l < 8 || l > 16);
}