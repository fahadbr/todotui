// #include "ncurses/window.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "todotxt/list.h"

void print_file();
void print_file_class();

int main() {
  std::cout << "hello there\n";
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
}

