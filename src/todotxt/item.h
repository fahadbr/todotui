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
  using Extensions = vector<std::pair<string, string>>;

  Item(const string);

  // default copy operations
  Item(const Item&) = default;
  Item& operator=(const Item&) = default;

  // default move operations
  Item(Item&&)  = default;
  Item& operator=(Item&&) = default;

  ~Item() = default;

  auto raw() const -> string;
  auto complete() const -> bool;
  auto priority() const -> char;
  auto contexts() const -> vector<string>;
  auto tags() const -> vector<string>;
  auto date_completed() const -> string;
  auto date_added() const -> string;
  auto extensions() const -> Extensions;

 private:
  enum State { kDateCompleted, kPriority, kDateAdded, kBody };

  string         raw_;
  bool           complete_;
  char           priority_;
  vector<string> contexts_;
  vector<string> tags_;
  string         date_completed_;
  string         date_added_;
  Extensions     extensions_;

  auto ProcessWord(const std::string_view, State&) -> void;
  auto ProcessBody(const std::string_view) -> void;
  auto ProcessDate(const std::string_view val, string& target_date) -> bool;
  auto PrintString() -> void;
};

inline auto ContainsItem(const vector<string>& vec, const std::string_view item) -> bool {
  if (vec.empty()) {
    return false;
  }
  for (auto& v : vec) {
    if (v == item) {
      return true;
    }
  }
  return false;
}

}  // namespace todo
#endif /* end of include guard:  */
