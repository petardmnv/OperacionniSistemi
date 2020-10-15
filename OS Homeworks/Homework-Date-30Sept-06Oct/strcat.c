//------------------------------------------------------------------------
// NAME: Petar Damyanov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: strcat.c
// FILE PURPOSE: Програма, която съединява два стринга;
// 
//
// ...
//------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
//------------------------------------------------------------------------
// FUNCTION: strcat
// Функцията съединява двата стринга в dest.
// PARAMETERS:
// size_t dest_len - Взимам дължината на dest, за да започна да записвам src след последния елемент на dest.
// 
//------------------------------------------------------------------------
char* strcat(char* dest, const char* src){
    size_t dest_len = strlen(dest);
    int i;
    for(i = 0; src[i] != '\0'; i++){
        dest[dest_len + i] = src[i];
    }
    //dest[dest_len + i + 1] = '\0';
    return dest;
}

int main()
{
    char a[30] = "I'am";
    char b[8] = "stupid.";
    printf("%s", strcat(a, b));
    return 0;
}