/******************************************************************************
 * File:             list.cpp
 *
 * Author:           Fahad Riaz
 * Created:          06/10/20
 * Description:      holds the list class
 *****************************************************************************/

#include "list.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace todo;
using std::cout;
using std::string;
using std::vector;

/******************************************************************************
 * Function:         List::List(const string filepath)
 *****************************************************************************/
List::List(const string& filepath) : handle_{filepath}, items_{} {
  string line;
  while (std::getline(handle_, line)) {
    if (line.size() > 0 && line.back() == '\r') {
      // cout << "removing carriage return" << '\n';
      line.pop_back();
    }
    items_.emplace_back(line);
  }
}

List::List(List&& oldlist) : handle_{std::move(oldlist.handle_)}, items_{std::move(oldlist.items_)} {
  oldlist.handle_ = std::fstream{};
  oldlist.items_  = vector<Item>{};
}

List& List::operator=(List&& oldlist) {
  std::swap(handle_, oldlist.handle_);
  std::swap(items_, oldlist.items_);
  return *this;
}

List::~List() {
  cout << "destroying list\n";
}

auto List::items() const -> const vector<Item>& {
  return items_;
}
