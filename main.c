#include "header.h"

void main(int argc,char *argv[]){
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  srand(time(NULL));
  int ch;
  VisitedTracker tr;
  Point * ans;
  A:
  clear();
  init_tracker(&tr);
  int cur_row = 0, cur_col = 0;
  int len_ans = 12;
  ans = (Point *)malloc(len_ans * sizeof(Point));
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
  while((ch = getch()) != 27){
    move_select(ch, &cur_row, &cur_col, ans, len_ans, &tr);
    if(ch == 'r'){
      clear_tracker(&tr);
      free(ans);
      goto A;
    }
  }
  clear_tracker(&tr);
  free(ans);
  endwin(); 
  return;
}