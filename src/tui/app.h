#pragma once

#include <cursesapp.h>

#include "todo/list.h"

namespace tui {

class MainApp : public NCursesApplication {
 private:
  todo::List list_;

 protected:
  int  titlesize() const;
  void title();

 public:
  MainApp(todo::List list);
  ~MainApp();
  int run();
};

}  // namespace tui
