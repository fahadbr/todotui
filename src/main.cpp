// #include "ncurses/window.h"
#include <iostream>

#include "todotxt/list.h"
#include "ncurses/window.h"

void print_file_class();

int main() {
  try {
    print_file_class();
  } catch (std::exception& ex) {
    std::cerr << "got exception: " << ex.what();
  } catch (...) {
    std::cerr << "caught exception.. exiting..\n";
    return 1;
  }

  return 0;
}

void print_file_class() {
  todo::List mainlist{"/data/syncthing/todo/main.todo.txt"};
  ncurses::DoStuff(mainlist);

  //auto w = NCursesWindow(10, 10, 0, 0);
  //ncurses::DoMoreStuff(&w);
}

