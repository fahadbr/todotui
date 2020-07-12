/******************************************************************************
 * File:             app.cpp
 *
 * Author:           Fahad Riaz
 * Created:          06/27/20
 * Description:
 *****************************************************************************/

#include "app.h"

#include <cursesm.h>

#include <iostream>
#include <string>

using namespace tui;
using namespace std;

MainApp::MainApp(todo::List list) : NCursesApplication(false), list_{std::move(list)} {
}

MainApp::~MainApp(){};

auto MainApp::titlesize() const -> int {
  return 1;
}

auto MainApp::title() -> void {
  const string titleText = "NCURSES Todotui in C++";
  titleWindow->bkgd(screen_titles());
  titleWindow->addstr(0, (titleWindow->cols() - titleText.size()) / 2, titleText.c_str());
  titleWindow->noutrefresh();
}


auto MainApp::CreateMenu() -> void {
  NCursesMenuItem** menu_items = new NCursesMenuItem*[list_.items().size() + 1];

  size_t i{0};
  for (auto& todo_item : list_.items()) {
    menu_items[i] = new NCursesMenuCallbackItem(&MainApp::PrintItem, todo_item.raw().c_str());
    // menu_items[i] = new NCursesMenuItem(todo_item.raw().c_str());
    i++;
  }

  // empty terminating item
  menu_items[i] = new NCursesMenuItem();

  int x, y;
  ::getmaxyx(stdscr, y, x);

  NCursesMenu menu{menu_items, y - 2, x * 2 / 3, 1, 1, false, true};

  auto subw = NCursesWindow(menu, true);
  menu.setSubWindow(subw);

  // menu.setSubWindow(nullptr);
  // menu.subWindow().wresize(LINES, COLS);
  menu.set_format(x - 2, 1);
  menu.box();
  // menu.refresh();

  menu();
  // int ch = getch();
}

auto MainApp::run() -> int {
  int x, y;
  ::getmaxyx(stdscr, y, x);

  auto height = y - 2;
  auto width  = x * 1 / 3 - 2;
  auto xpos   = x * 2 / 3 + 2;
  auto ypos   = 1;

  auto smallwin = NCursesPanel(height, width, ypos, xpos);
  smallwin.box();
  smallwin.show();
  smallwin.refresh();

  CreateMenu();

  return 0;
}

