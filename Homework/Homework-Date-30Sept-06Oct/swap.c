//------------------------------------------------------------------------
// NAME: Petar Damyanov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: swap.c
// FILE PURPOSE: Задачата трябва да размени стойностите на две числа.
// 
//
// ...
//------------------------------------------------------------------------

#include <stdio.h>
//------------------------------------------------------------------------
// FUNCTION: swap
// Функцията разменя стойностите на две числа.
// PARAMETERS:
// int c - Проименливата присвоява стойността на поинтъра, а след това я използвам, за да задам стойността и на b. 
// 
//------------------------------------------------------------------------
void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

int main()
{
    int a = 10;
    int b = 5;
    swap(&a, &b);
    printf("%d %d", a, b);
    return 0;
}
