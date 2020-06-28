#pragma once

#include <ncurses.h>
#include <cursesw.h>
#include "todo/list.h"

namespace ncurses {


class Window {
public:
  //TODO remove
  Window() {
    win_ = nullptr;
  }

  Window(int height, int width, int starty, int startx);
  ~Window();

  void Refresh();

private:
  WINDOW* win_;
};

void DoStuff(todo::List& list);

void DoMoreStuff(todo::List& list);

} // namespace ncurses
