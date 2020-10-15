//------------------------------------------------------------------------
// NAME: Petar Damyanov
// CLASS: XIb
// NUMBER: 21
// PROBLEM: #1
// FILE NAME: stack.c
// FILE PURPOSE: В задачата трябва да се реализира библиотека stack.
// 
//
// ...
//------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    size_t size;
    size_t capacity;
    int *elements;
} stack;

//------------------------------------------------------------------------
// FUNCTION: stack_init
// Функцията инициализира елементите на структурата
// PARAMETERS: my_stack. Заделям място за елементите на стака и сайза става 0.
// 
// 
//------------------------------------------------------------------------
void stack_init(stack* my_stack){
    my_stack->elements = (int*)malloc(sizeof(int) * my_stack->capacity);
    my_stack->size = 0;
}

//------------------------------------------------------------------------
// FUNCTION: stack_destroy
// Функцията деинициализира структурата.
// PARAMETERS: my_stack.Премахвам елементите в elements и сайза става 0.
//  
// 
//------------------------------------------------------------------------
void stack_destroy(stack* my_stack){
    free(my_stack->elements);
    my_stack->size = 0;
}

//------------------------------------------------------------------------
// FUNCTION: stack_empty
// Функцията проверява дали подадения като аргумент стек е празен.
// PARAMETERS:my_stack. Проверявам сайза ако не е нула връщам 0.
// 
// 
//------------------------------------------------------------------------
int stack_empty(stack* my_stack){
    if (my_stack->size != 0){
        return 0;
    }else {
        return 1;
    }
}

//------------------------------------------------------------------------
// FUNCTION: stack_push
// Функцията добавя елемент към стека.
// PARAMETERS: my_stack и val. Записвам val в elements[size] и давам size++ след като съм записал вал в елементс.Ако
// стака е пълен принтирам лорнинг.
// 
//------------------------------------------------------------------------
void stack_push(stack* my_stack, int val){
    if (my_stack->capacity > my_stack->size){
        my_stack->elements[my_stack->size++] = val;
    }else {
        printf("Stack is full");
    }
}

//------------------------------------------------------------------------
// FUNCTION: stack_top
// Функцията връща последния добавен елемент към стека.
// PARAMETERS: my_stack. Връщам елемента от цайз минус 1 защото в push увеличавам след като добавя елемент.
//  Ако стака е празен принтирам лорнинг.
// 
//------------------------------------------------------------------------
int stack_top(stack* my_stack){
        if (stack_empty(my_stack) == 1){
        printf("Your stack is empty.");
    }else {
        return my_stack->elements[my_stack->size - 1];
    }
}

//------------------------------------------------------------------------
// FUNCTION: stack_pop
// Функцията ремахва последния добавен елемент от стека.
// PARAMETERS:my_stack. Изваждам 1 от сайза. Ако стака е празен
// принтирам лорнинг.
// 
//------------------------------------------------------------------------
void stack_pop(stack* my_stack){
    if (stack_empty(my_stack) == 1){
        printf("Your stack is empty.");
    }else {
        my_stack->size--;
    }
}

int main()
{
    stack main_stack;
    main_stack.capacity = 6;
    stack_init(&main_stack);
    int is_empty = stack_empty(&main_stack);
    printf("%d", is_empty);
    for (int i = 0; i < 4; i++) {
        stack_push(&main_stack, 2 + i);
        printf("%d size - %d\n", stack_top(&main_stack), main_stack.size);
    }
    for (int i = 0; i < 4; i++) {
        printf("%d\n", stack_top(&main_stack));
        stack_pop(&main_stack);
    }
    //stack_pop(main_stack);
    //stack_pop(main_stack);
    /*stack_destroy(&main_stack);
    is_empty = stack_empty(&main_stack);
    printf("%d", is_empty);*/
    
    return 0;
}