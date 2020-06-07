#include "window.h"
#include <iostream>

Window::Window(int height, int width, int starty, int startx) {
  std::cout << "made a new window\n";
  win_ = newwin(height, width, starty, startx);
}

Window::~Window() {
  if (win_ != nullptr) {
    int res = delwin(win_);
    std::cout << "destroyed a window. code: " << res << "\n";
  }
}

void Window::Refresh() { wrefresh(win_); }

void demo1() {
  initscr();            // start curses mode
  raw();                // line buffering disabled
  keypad(stdscr, TRUE); // we get F1 F2 etc
  noecho();             // dont echo() while we do getch

  printw("Type any character to see it in bold\n"); // print hello world
  int ch = getch();
  if (ch == KEY_F(1))
    printw("F1 key pressed");
  else {
    printw("The pressed key is ");
    attron(A_BOLD);
    printw("%c", ch);
    attroff(A_BOLD);
  }

  refresh(); // print it on to the real screen
  getch();   // wait for user input
  endwin();  // end curses mode
}
