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

auto PrintItem(NCursesMenuItem& i) -> bool {
  ::move(LINES - 1, 1);
  ::clrtoeol();
  ::mvprintw(LINES - 1, 1, i.name());
  return false;
}

auto MainApp::CreateMenu() -> void {
  NCursesMenuItem** menu_items = new NCursesMenuItem*[list_.items().size() + 1];

  size_t i{0};
  for (auto& todo_item : list_.items()) {
    menu_items[i] = new NCursesMenuCallbackItem(&PrintItem, todo_item.raw().c_str());
    // menu_items[i] = new NCursesMenuItem(todo_item.raw().c_str());
    i++;
  }

  // empty terminating item
  menu_items[i] = new NCursesMenuItem();

  int x, y;
  getmaxyx(stdscr, y, x);

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
  getmaxyx(stdscr, y, x);

  auto smallwin = NCursesPanel(y - 2, x * 1 / 3 - 2, 1, x * 2 / 3 + 2);
  smallwin.box();
  smallwin.show();
  smallwin.refresh();

  CreateMenu();

  return 0;
}
