#pragma once

#include <string>
#include <vector>

namespace todo {

using std::string;
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

  auto raw() const -> const string&;
  auto complete() const -> bool;
  auto priority() const -> char;
  auto contexts() const -> const vector<string>&;
  auto tags() const -> const vector<string>&;
  auto date_completed() const -> const string&;
  auto date_added() const -> const string&;
  auto due_date() const -> const string&;
  auto threshold_date() const -> const string&;
  auto hidden() const -> bool;
  auto recurrance() const -> const string&;
  auto extensions() const -> const Extensions&;

 private:
  enum State { kDateCompleted, kPriority, kDateAdded, kBody };

  string         raw_;
  bool           complete_;
  char           priority_;
  vector<string> contexts_;
  vector<string> tags_;
  string         date_completed_;
  string         date_added_;
  string         due_date_;
  string         threshold_date_;
  bool           hidden_;
  string         recurrance_;
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
