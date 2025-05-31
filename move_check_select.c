#include "header.h"

static int num_of_tyles = ROW * COL;

void lost(int row, int col){
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

void zone_search(int cur_row, int cur_col, int row, int col, Point ans[], int len_ans) {
    Point *visit = malloc(row * col * sizeof(Point));
    if (!visit) return;  
    
    el *stack = NULL;
    int step = 0;
    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    
    Point start = {cur_col, cur_row};
    push(&stack, start);
    
    while(stack) {
        Point c = pop(&stack);
        
        if (visited(visit, c, step) || 
            c.x < 0 || c.x >= col || c.y < 0 || c.y >= row || check_ans(c.y, c.x, ans, len_ans)) {
            continue;
        }
        
        visit[step++] = c;
        num_of_tyles--;
        
        move(c.y, c.x);
        int a = check_adj(c.y, c.x, ans, len_ans);
        refresh();
        if (!a) continue;
        
        for(int i = 0; i < 8; i++) {
            Point neighbor = {c.x + dx[i], c.y + dy[i]};
            if (neighbor.x >= 0 && neighbor.x < col && neighbor.y >= 0 && neighbor.y < row && !visited(visit, neighbor, step)) {
                push(&stack, neighbor);
            }
        }
    }
    
    free(visit);
    move(cur_row, cur_col);
    return;
}

int move_select(int ch, int* cur_row, int* cur_col, int row, int col, Point ans[], int len_ans){
    static int win_count = 0;
    switch(ch){
            case KEY_UP:
                if(*cur_row > 0){
                    move(--*cur_row, *cur_col);
                    refresh();
                }
            break;
            case KEY_DOWN:
                if(*cur_row < row-1){
                    move(++*cur_row, *cur_col);
                    refresh();
                }
            break;
            case KEY_RIGHT:
                if(*cur_col < col - 1){
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
                    zone_search(*cur_row, *cur_col, row, col, ans, len_ans);
                else{
                    lost(row, col);
                    return 0;
                }
            break;
            case 'b':
                printw("B");
                move(*cur_row, *cur_col);
                if(check_ans(*cur_row, *cur_col, ans, len_ans)){
                    win_count++;
                    num_of_tyles--;
                }
            break;
            case 'c':
                int c = getch();
                if(c == 'b') printw(".");
                move(*cur_row, *cur_col);
                if(check_ans(*cur_row, *cur_col, ans, len_ans)){
                    win_count--;
                    num_of_tyles++;
                }
            break;
        }
        if(win_count == len_ans && num_of_tyles == 0){
                    clear();
                    move(0,0);
                    printw("YOU WON");
                };
    return 0;
}