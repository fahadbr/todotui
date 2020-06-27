#ifndef WINDOW_H_U5VPFMQ7
#define WINDOW_H_U5VPFMQ7

#include <ncurses.h>
//#include <cursesw.h>
#include "todotxt/list.h"

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

//void DoMoreStuff(NCursesWindow* w);

} // namespace ncurses


#endif /* end of include guard: WINDOW_H_U5VPFMQ7 */
