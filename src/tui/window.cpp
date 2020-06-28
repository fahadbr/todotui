#include "window.h"

#include "todo/list.h"

#include <iostream>

using namespace ncurses;
using namespace std;

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

void Window::Refresh() {
  wrefresh(win_);
}

void ncurses::DoStuff(todo::List& list) {
  initscr();             // start curses mode
  raw();                 // line buffering disabled
  keypad(stdscr, TRUE);  // we get F1 F2 etc
  noecho();              // dont echo() while we do getch

  for (auto& item : list.items()) {
    printw(item.raw().c_str());  // print hello world
    printw("\n");
  }

  int ch = getch();
  printw("The pressed key is ");
  attron(A_BOLD);
  printw("%c", ch);
  attroff(A_BOLD);

  refresh();  // print it on to the real screen
  getch();    // wait for user input
  endwin();   // end curses mode
}

void ncurses::DoMoreStuff(todo::List& list) {
}
