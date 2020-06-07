#ifndef WINDOW_H_U5VPFMQ7
#define WINDOW_H_U5VPFMQ7

#include <ncurses.h>

class Window {
public:
  //TODO remove
  Window() {
    win_ = nullptr;
  }

  Window(int height, int width, int starty, int startx);
  virtual ~Window();

  void Refresh();

private:
  WINDOW* win_;
};
#endif /* end of include guard: WINDOW_H_U5VPFMQ7 */
