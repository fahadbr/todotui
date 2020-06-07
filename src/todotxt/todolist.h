#ifndef TODOLIST_H_TFD9B3BW
#define TODOLIST_H_TFD9B3BW

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace todo {

using std::string;
using std::unordered_map;
using std::vector;

class Item {
public:
  Item(const string);

  // default copy operations
  Item(const Item &) = default;
  Item &operator=(const Item &) = default;

  // default move operations
  Item(Item &&) = default;
  Item &operator=(Item &&) = default;

  ~Item();

  string raw();
  bool complete();
  char priority();
  vector<string> contexts();
  vector<string> tags();
  string date_completed();
  string date_added();
  unordered_map<string, string> extensions();

private:
  string raw_;
  bool complete_;
  char priority_;
  vector<string> contexts_;
  vector<string> tags_;
  string date_completed_;
  string date_added_;
  unordered_map<string, string> extensions_;
};

class List {
public:
  List(const string);

  // ensure no copying
  List(const List &) = delete;
  List &operator=(const List &) = delete;

  List(List &&);
  List &operator=(List &&);

  ~List();

  vector<Item> items();

private:
  std::fstream handle_;
  vector<Item> items_;
};



} // namespace todo
#endif /* end of include guard:  */
