/* imports */
#include <ncurses.h>
#include <stdio.h>

#include "headers/meca.h"

/* data structures */
struct editorSettings {
  int screencols;
  int screenrows;
  int cx, cy;
};
struct editorSettings E;

void editorDrawRows() {
  wmove(stdscr, 0, 0);
  int i;
  for (i = 0; i < E.screenrows; i++) {
    // print welcome message at one third down the screen
    if (i == E.screenrows/3) {
      printw("~\n\r");
      char welcome[80];
      int welcomelen = snprintf(welcome, sizeof(welcome),
        "meca editor -- version %s", MECA_VERSION);
      mvprintw(i, ((E.screencols - welcomelen) / 2)-1, "%s", welcome);
      printw("\n\r");
      continue;
    }
    printw("~\n\r");
  }
  wmove(stdscr, E.cy, E.cx);
}

/* init */
void initEditor() {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();

  // settings
  getmaxyx(stdscr, E.screenrows, E.screencols);
  E.cx = 0;
  E.cy = 0;
}

int main() {
  initEditor();
  editorDrawRows();
  getch();
  endwin();
  return 0;
}
