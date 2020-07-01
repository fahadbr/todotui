#include <iostream>

#include "tui/app.h"
#include "todo/list.h"

void print_file_class();

int main() {
  try {
    print_file_class();
  } catch (std::exception& ex) {
    std::cerr << "got exception: " << ex.what() << std::endl;
  } catch (NCursesException& ex) {
    std::cerr << "got ncurses exception: " << ex.message << std::endl;
    std::cerr << "code: " << ex.errorno << std::endl;
  } catch (...) {
    std::cerr << "caught unknown exception.. exiting..\n";
    return 1;
  }

  return 0;
}

void print_file_class() {
  todo::List mainlist{"/data/syncthing/todo/main.todo.txt"};

  auto app = tui::MainApp(std::move(mainlist));
  app();
}

