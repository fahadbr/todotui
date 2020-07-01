#pragma once

#include <cursesapp.h>

#include "todo/list.h"

namespace tui {

class MainApp : public NCursesApplication {
 private:
  todo::List list_;

  auto CreateMenu() -> void;

 protected:
  auto titlesize() const -> int override;
  auto title() -> void override;

 public:
  MainApp(todo::List list);
  ~MainApp();

  auto run() -> int override;
};

}  // namespace tui
