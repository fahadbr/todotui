#ifndef TODOTXT_ITEM_H
#define TODOTXT_ITEM_H

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

  ~Item() = default;

  string raw();
  bool complete();
  char priority();
  vector<string> contexts();
  vector<string> tags();
  string date_completed();
  string date_added();
  unordered_map<string, string> extensions();

private:
  enum State { kDateCompleted, kPriority, kDateAdded, kBody };

  string raw_;
  bool complete_;
  char priority_;
  vector<string> contexts_;
  vector<string> tags_;
  string date_completed_;
  string date_added_;
  unordered_map<string, string> extensions_;

  void process_word(const std::string_view, State&);
  void process_body(const std::string_view);
  bool process_date(const std::string_view val, string& target_date);
  void print_string();
};


} // namespace todo
#endif /* end of include guard:  */
