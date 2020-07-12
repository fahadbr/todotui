#pragma once

#include <cursesapp.h>
#include <cursesm.h>

#include "todo/list.h"

namespace tui {

class MainApp : public NCursesApplication {
 private:
  todo::List list_;

  auto CreateMenu() -> void;

  static auto PrintItem(NCursesMenuItem& i) -> bool {
    ::move(LINES - 1, 1);
    ::clrtoeol();
    ::mvprintw(LINES - 1, 1, i.name());
    return false;
  }

 protected:
  auto titlesize() const -> int override;
  auto title() -> void override;

 public:
  MainApp(todo::List list);
  ~MainApp();

  auto run() -> int override;
};

}  // namespace tui
