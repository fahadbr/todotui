/******************************************************************************
 * File:             item.cpp
 *
 * Author:           Fahad Riaz
 * Created:          06/10/20
 * Description:      holds the item class
 *****************************************************************************/

#include "item.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace todo;

using std::cout;
using std::string;
using std::string_view;
using std::unordered_map;
using std::vector;

Item::Item(const string rawinput)
    : m_raw{rawinput},
      m_complete{false},
      m_priority{0},
      m_contexts{},
      m_tags{},
      m_date_completed{},
      m_date_added{},
      m_due_date{},
      m_threshold_date{},
      m_hidden{false},
      m_recurrance{},
      m_extensions{} {
  using ssize_t = std::string::size_type;

  if (rawinput.length() == 0) {
    throw std::exception{};
  }

  if (rawinput.at(0) == 'x') {
    m_complete = true;
  }

  // if we see a completion marker, first look for the completion date
  // otherwise look for the priority
  State loop_state{m_complete ? kDateCompleted : kPriority};

  const uint8_t delim     = ' ';
  ssize_t       start_pos = rawinput.find_first_not_of(delim, m_complete ? 1 : 0);
  ssize_t       delim_pos = rawinput.find_first_of(delim, start_pos);

  while (string::npos != start_pos || string::npos != delim_pos) {
    ssize_t     end_pos{delim_pos == string::npos ? rawinput.length() : delim_pos};
    ssize_t     val_len{end_pos - start_pos};
    string_view val{&rawinput.at(start_pos), val_len};
    // string val = rawinput.substr(start_pos, end_pos);

    ProcessWord(val, loop_state);
    start_pos = rawinput.find_first_not_of(delim, delim_pos);
    delim_pos = rawinput.find_first_of(delim, start_pos);
  }

  // PrintString();
}

auto Item::ProcessWord(const string_view val, Item::State& loop_state) -> void {
  switch (loop_state) {
    case kDateCompleted:
      loop_state = kPriority;
      if (ProcessDate(val, m_date_completed)) {
        break;
      }
    case kPriority:
      loop_state = kDateAdded;
      // Check for priority
      if (val.length() == 3 && val[0] == '(' && val[2] == ')') {
        m_priority = val[1];
        // cout << rawinput << '\n';
        break;
      }
    case kDateAdded:
      loop_state = kBody;
      if (ProcessDate(val, m_date_added)) {
        break;
      }
    case kBody:
      ProcessBody(val);
      break;
  }
}

auto Item::ProcessBody(const string_view item) -> void {
  switch (item.at(0)) {
    case '@': {
      string_view ctx{&item.at(1), item.length() - 1};
      if (!ContainsItem(m_contexts, ctx)) {
        m_contexts.emplace_back(ctx);
      }
      break;
    }
    case '+': {
      string_view tag{&item.at(1), item.length() - 1};
      if (!ContainsItem(m_tags, tag)) {
        m_tags.emplace_back(tag);
      }
      break;
    }
    default:
      auto colon_pos = item.find(':');
      if (colon_pos != string::npos) {
        auto key = item.substr(0, colon_pos);
        auto val = item.substr(colon_pos + 1);

        if (key == "h" && val == "1") {
          m_hidden = true;
          return;
        } else if (key == "due" && ProcessDate(val, m_due_date)) {
          return;
        } else if (key == "t" && ProcessDate(val, m_threshold_date)) {
          return;
        } else if (key == "rec") {
          m_recurrance = val;
          return;
        }

        m_extensions.emplace_back(key, val);
      }
  }
}

auto Item::ProcessDate(const string_view val, string& target_date) -> bool {
  if (val.length() != 10) {
    return false;
  }

  for (int i = 0; i < val.length(); i++) {
    switch (i) {
      case 5:
        if (val[i] < '0' || val[i] > '1') {
          return false;
        }
        break;
      case 8:
        if (val[i] < '0' || val[i] > '3') {
          return false;
        }
        break;
      case 4:
      case 7:
        if (val[i] != '-') {
          return false;
        }
        break;
      default:
        if (val[i] < '0' || val[i] > '9') {
          return false;
        }
    }
  }
  target_date = val;
  return true;
}

auto Item::PrintString() -> void {
  cout << "raw: " << m_raw << '\n';
  cout << "complete: " << m_complete << "\n";
  cout << "date_completed: " << m_date_completed << "\n";
  cout << "priority: " << m_priority << '\n';
  cout << "date_added: " << m_date_added << "\n";

  cout << "contexts: ";
  std::copy(m_contexts.begin(), m_contexts.end(), std::ostream_iterator<string>(cout, " "));
  cout << '\n';

  cout << "tags: ";
  std::copy(m_tags.begin(), m_tags.end(), std::ostream_iterator<string>(cout, " "));
  cout << "\n";

  cout << "extensions: ";
  for (auto& p : m_extensions) {
    cout << p.first << ":" << p.second << " ";
  }
  cout << "\n\n";
}

