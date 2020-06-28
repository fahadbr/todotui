#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "item.h"

namespace todo {

using std::string;
using std::unordered_map;
using std::vector;

class List {
 public:
  List(const string&);

  // ensure no copying
  List(const List&) = delete;
  List& operator=(const List&) = delete;

  List(List&&);
  List& operator=(List&&);

  ~List();

  auto items() const -> const vector<Item>&;

 private:
  std::fstream handle_;
  vector<Item> items_;
};

}  // namespace todo
