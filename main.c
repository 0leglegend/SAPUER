#include "header.h"

void main(int argc,char *argv[]){
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  int row = 10, col = 12;
  int ch,cur_row = 0, cur_col = 0;
  Point ans[] = {{2,2}};
  int len_ans = 5;
  for (int i = 0; i < 10;){
    for (int j = 0; j < 12; j++){
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