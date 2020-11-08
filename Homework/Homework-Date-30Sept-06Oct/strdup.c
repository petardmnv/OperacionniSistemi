//------------------------------------------------------------------------
// NAME: Petar Damyanov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: strdup.c
// FILE PURPOSE: Задачата трябва да записва указател към новозаделена динамична памет, копие на подаден стринг като аргумент.
// 
//
// ...
//------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//------------------------------------------------------------------------
// FUNCTION: strdup
// Функцията записва указател към новозаделена динамична памет, копие на подаден стринг като аргумент.
// PARAMETERS:
// Първо заделям памет в new_str, колкото е голяма дължината на curr_str и добавям 1 заради терминиращата нула и 
// копирам curr_str в new_str. 
// 
//------------------------------------------------------------------------
char* strdup( const char * curr_str){
    char* new_str = malloc(strlen(curr_str) + 1);
    strcpy(new_str, curr_str);
    return new_str;
}

int main()
{
    const char my_str[4] = "bye";
    printf("%s", strdup(my_str));
    return 0;
}