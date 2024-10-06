#include <ncurses.h>

int main() {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  int ch;
  while (1) {
    ch = getch();
    if (ch == KEY_F(1))
      printw("pressed %c", ch);
    else {
      attron(A_BOLD);
      printw("%c", ch);
      attroff(A_BOLD);
    }
    refresh();
  }
  endwin();
  return 0;
}
