#include <ncurses.h>
#include <string.h>

int main() {
  char mesg[] = "Just a string";
  int row, col;
  initscr();
  getmaxyx(stdscr, row, col);
  raw();
  keypad(stdscr, TRUE);
  noecho();
  mvprintw(row/2, (col-strlen(mesg))/2, "%s", mesg);
  mvprintw(row-2, 0, "This screen ahs %d rows and %d columns\n", row, col);
  printw("Try resizing your window and then run this program again");
  getch();
  endwin();
  return 0;
}
