#include "todolist.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace todo;
using std::string;
using std::unordered_map;
using std::vector;

Item::Item(const string rawinput) : raw_{rawinput} {
  std::cout << rawinput << '\n';

  std::istringstream raw_stream{rawinput};
  while (!raw_stream.eof()) {
    string val;
    raw_stream >> val;
    std::cout << val << '\n';
  }
}

Item::~Item() {}

string Item::raw() { return raw_; }

bool Item::complete() { return complete_; };
char Item::priority() { return priority_; };
vector<string> Item::contexts() { return contexts_; };
vector<string> Item::tags() { return tags_; };
string Item::date_completed() { return date_completed_; };
string Item::date_added() { return date_added_; };
unordered_map<string, string> Item::extensions() { return extensions_; };

List::List(const string filepath) : handle_{filepath}, items_{} {
  string line;
  while (std::getline(handle_, line)) {
    items_.push_back(Item{line});
  }
}

List::List(List &&oldlist)
    : handle_{std::move(oldlist.handle_)}, items_{std::move(oldlist.items_)} {

  oldlist.handle_ = std::fstream{};
  oldlist.items_ = vector<Item>{};
}

List &List::operator=(List &&oldlist) {
  std::swap(handle_, oldlist.handle_);
  std::swap(items_, oldlist.items_);
  return *this;
}

List::~List() { std::cout << "destroying list\n"; }

vector<Item> List::items() { return items_; }
