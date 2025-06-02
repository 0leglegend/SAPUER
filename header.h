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

typedef struct{
    Point * visit;
    int number;
}VisitedTracker;

typedef struct elem{
    Point point;
    struct elem * prev;
}el;
void push(el** stack, Point p);
Point pop(el** stack);
void free_stack(el ** stack);
int move_select(int ch, int* cur_row, int* cur_col, Point ans[], int len_ans, VisitedTracker * tr);
void init_tracker(VisitedTracker * tr);
void clear_tracker(VisitedTracker * tr);
#endif