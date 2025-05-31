#include "header.h"

void main(int argc,char *argv[]){
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  srand(time(NULL));
  int row = ROW, col = COL;
  int ch,cur_row = 0, cur_col = 0;
  int len_ans = 2;
  Point * ans = (Point *)malloc(len_ans * sizeof(Point));
  for (int i = 0; i < len_ans; i++){
    (ans + i)->x = rand() % COL;
    (ans + i)->y = rand() % ROW;
  }
  for (int i = 0; i <= ROW;){
    for (int j = 0; j < COL; j++){
      printw(".");
    }
    move(i++,0);
  }
  move(0,0);
  refresh();
  while((ch = getch()) != 27)
    move_select(ch, &cur_row, &cur_col, row, col, ans, len_ans);
  endwin(); 
  return;
}