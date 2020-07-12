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

  auto raw() const -> const string& {
    return m_raw;
  }
  auto complete() const -> bool {
    return m_complete;
  }
  auto priority() const -> char {
    return m_priority;
  }
  auto contexts() const -> const vector<string>& {
    return m_contexts;
  }
  auto tags() const -> const vector<string>& {
    return m_tags;
  }
  auto date_completed() const -> const string& {
    return m_date_completed;
  }
  auto date_added() const -> const string& {
    return m_date_added;
  }
  auto due_date() const -> const string& {
    return m_due_date;
  }
  auto threshold_date() const -> const string& {
    return m_threshold_date;
  }
  auto hidden() const -> bool {
    return m_hidden;
  }
  auto recurrance() const -> const string& {
    return m_recurrance;
  }
  auto extensions() const -> const Extensions& {
    return m_extensions;
  }

 private:
  enum State { kDateCompleted, kPriority, kDateAdded, kBody };

  string         m_raw;
  bool           m_complete;
  char           m_priority;
  vector<string> m_contexts;
  vector<string> m_tags;
  string         m_date_completed;
  string         m_date_added;
  string         m_due_date;
  string         m_threshold_date;
  bool           m_hidden;
  string         m_recurrance;
  Extensions     m_extensions;

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
