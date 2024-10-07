/* imports */
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/meca.h"

/* data structures */
typedef struct {
  char *buf;
  int len;
}lineBuffer;

struct editorSettings {
  int screencols;
  int screenrows;
  int cx, cy;
  char *filename;
  lineBuffer* lines;
  int lineCount;
};
struct editorSettings E;

void editorClose() {
  endwin();
}

/* file i/o */
void editorOpen(char *filepath) { E.filename = filepath; }

/* line buffer */

#define NEW_LINE {NULL, 0}

/* rendering */
void editorDrawRows() {
  wmove(stdscr, 0, 0);
  int i;
  for (i = 0; i < E.screenrows; i++) {
    // print welcome message at one third down the screen
    if (i == E.screenrows / 3) {
      printw("~\n\r");
      char welcome[80];
      int welcomelen = snprintf(welcome, sizeof(welcome),
                                "meca editor -- version %s", MECA_VERSION);
      if (welcomelen > E.screencols)
        welcomelen = E.screencols;
      mvprintw(i, ((E.screencols - welcomelen) / 2) - 1, "%s", welcome);
      printw("'%s'", E.filename);
      printw("\n\r");
      continue;
    }
    printw("~\n\r");
  }
  wmove(stdscr, E.cy, E.cx);
}

void editorProcessKeypress() {
  int ch = getch();
  getyx(stdscr, E.cy, E.cx);
  switch (ch) {
  case 263:
    E.cx--;
    wmove(stdscr, (E.cy), (E.cx));
    wdelch(stdscr);
    break;
  case 'q':
    exit(0);
    break;
  default:
    waddch(stdscr, (ch));
    break;
  }
}

/* init */
void initEditor() {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  atexit(editorClose);

  // settings
  getmaxyx(stdscr, E.screenrows, E.screencols);
  E.cx = 0;
  E.cy = 0;
  E.filename = NULL;
  E.lines = NULL;
  E.lineCount = 0;
}

int main(int argc, char **argv) {
  initEditor();

  // open a file it existent
  if (argc >= 2) {
    editorOpen(argv[1]);
  }

  editorDrawRows();
  while (1) {
    editorProcessKeypress();
    refresh();
  }
  endwin();
  return 0;
}
