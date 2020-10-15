//------------------------------------------------------------------------
// NAME: Petar Damyanov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: string.c
// FILE PURPOSE: Програма, която проверяваща гължината на стринг.
// 
//
// ...
//------------------------------------------------------------------------

#include <stdio.h>
//------------------------------------------------------------------------
// FUNCTION: strlenn
// Функцията намира дължината на стринг.
// PARAMETERS:
// size_t current_len - Променливата, на която записвам дължината на стринга.
// int i - брояч
//------------------------------------------------------------------------
size_t strlenn(const char* my_string){
    size_t current_len = 0;
    for (int i = 0; my_string[i] != '\0' ; i++) {
        current_len++;
    }
    return current_len;
}

int main()
{
    printf("%ld\n", strlenn("asdffg"));
    return 0;
}
