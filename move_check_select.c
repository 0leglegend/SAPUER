#include "header.h"


void lost(){
    printw("O");
    move(0,0);
    clear();
    printw("YOU LOST");
    refresh();
}

int check_ans(int cur_row, int cur_col, Point ans[], int len_ans){
    for(int i = 0; i < len_ans; i++){
        if(cur_col == (ans + i)->x && cur_row == (ans + i)->y){
            return 1;
        }
    }
    return 0;
}

int check_adj(int cur_row, int cur_col, Point ans[], int len_ans){
    int count = 0;
    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    for(int i = 0; i < 8; i++)
        if(check_ans((cur_row + dy[i]), (cur_col + dx[i]), ans, len_ans)) count++;
    if(!count){
        printw("E");
        return 1;
    }
    else{
        printw("%d", count);
        return 0;
    }
}

int visited(Point arr[], Point p, int step){
    for (int i = 0; i < step; i++){
        if(arr[i].x == p.x && arr[i].y == p.y) return 1;
    }
    return 0;
}

void zone_search(int cur_row, int cur_col, Point ans[], int len_ans, VisitedTracker * tr){ 
    el *stack = NULL;
    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    
    Point start = {cur_col, cur_row};
    push(&stack, start);
    
    while(stack) {
        refresh();
        Point c = pop(&stack);
        
        if (visited(tr->visit, c, tr->number) || 
            c.x < 0 || c.x >= COL || c.y < 0 || c.y >= ROW || check_ans(c.y, c.x, ans, len_ans)) {
            continue;
        }
        
        tr->visit[tr->number++] = c;
        
        move(c.y, c.x);
        if (!check_adj(c.y, c.x, ans, len_ans)) continue;
        
        for(int i = 0; i < 8; i++) {
            Point neighbor = {c.x + dx[i], c.y + dy[i]};
            if (neighbor.x >= 0 && neighbor.x < COL && neighbor.y >= 0 && neighbor.y < ROW && !visited(tr->visit, neighbor, tr->number)) {
                push(&stack, neighbor);
            }
        }
    }
    move(cur_row, cur_col);
    return;
}

int move_select(int ch, int* cur_row, int* cur_col, Point ans[], int len_ans, VisitedTracker * tr){
    static int win_count = 0;
    switch(ch){
            case KEY_UP:
                if(*cur_row > 0){
                    move(--*cur_row, *cur_col);
                    refresh();
                }
            break;
            case KEY_DOWN:
                if(*cur_row < ROW-1){
                    move(++*cur_row, *cur_col);
                    refresh();
                }
            break;
            case KEY_RIGHT:
                if(*cur_col < COL - 1){
                    move(*cur_row, ++*cur_col);
                    refresh();
                }
            break;
            case KEY_LEFT:
                if(*cur_col > 0){
                    move(*cur_row, --*cur_col);
                    refresh();
                }
            break;
            case 'f':
                if(!(check_ans(*cur_row, *cur_col, ans, len_ans)))
                    zone_search(*cur_row, *cur_col, ans, len_ans, tr);
                else{
                    lost();
                    printw("\n%d\\%d bombs", win_count, len_ans);
                    win_count = 0;
                }
            break;
            case 'b':
                printw("B");
                move(*cur_row, *cur_col);
                if(check_ans(*cur_row, *cur_col, ans, len_ans)){
                    win_count++;
                }
            break;
    }
    if((tr->number + win_count) == ROW * COL){
        clear();
        move(0,0);
        win_count = 0;
        printw("YOU WON");
    }
    return 0;
}

void init_tracker(VisitedTracker * tr){
    tr->visit = (Point *)malloc(ROW * COL * sizeof(Point));
    tr->number = 0;
    return;
}

void clear_tracker(VisitedTracker * tr){
    if(tr->visit != NULL) free(tr->visit);
    tr->visit = NULL;
    tr->number = 0;
    return;
}