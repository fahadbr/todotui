/******************************************************************************
 * File:             app.cpp
 *
 * Author:           Fahad Riaz
 * Created:          06/27/20
 * Description:
 *****************************************************************************/

#include "app.h"

#include <cursesm.h>

#include <string>

using namespace tui;
using namespace std;

MainApp::MainApp(todo::List list) : NCursesApplication(false), list_{std::move(list)} {
}

MainApp::~MainApp(){};

int MainApp::titlesize() const {
  return 1;
}

void MainApp::title() {
  const string titleText = "todotui in C++";
  titleWindow->bkgd(screen_titles());
  titleWindow->addstr(0, (titleWindow->cols() - titleText.size()) / 2, titleText.c_str());
  titleWindow->noutrefresh();
}

int MainApp::run() {
  NCursesMenuItem** menu_items = new NCursesMenuItem*[list_.items().size() + 1];

  size_t i{0};
  for (auto& todo_item : list_.items()) {
    menu_items[i] = new NCursesMenuItem(todo_item.raw().c_str());
    i++;
  }

  // empty terminating item
  menu_items[i] = new NCursesMenuItem();

  NCursesMenu menu{menu_items, true, true};
  menu();
  // int ch = getch();

  return 0;
}
