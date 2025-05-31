#ifndef SAPEUR
#define SAPUER
#include<ncurses.h>
#include<stdlib.h>
#include<time.h>

#define ROW 10
#define COL 13

typedef struct{
    int x;
    int y;
}Point;

typedef struct elem{
    Point point;
    struct elem * prev;
}el;
void push(el** stack, Point p);
Point pop(el** stack);
void free_stack(el ** stack);
int move_select(int ch, int* cur_row, int* cur_col, int row, int col, Point ans[], int len_ans);
#endif