#include"header.h"

void push(el** stack, Point p){
    el * tmp = (el *)malloc(sizeof(el));
    if(tmp){
        tmp->point = p;
        tmp->prev = *stack;
        *stack = tmp;
    }
    return;
}

Point pop(el** stack){
    Point res;
    el* tmp = NULL;
    if(stack){
        res = (*stack)->point;
        tmp = *stack;
        *stack = tmp->prev;
        free(tmp);
    }
    return res;
}

void free_stack(el ** stack){
    while((*stack)->prev != NULL){
        pop(stack);
    }
}