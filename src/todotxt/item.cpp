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

Item::Item(const string rawinput) : raw_{rawinput} {
  using ssize_t = std::string::size_type;

  if (rawinput.length() == 0) {
    throw std::exception{};
  }

  if (rawinput.at(0) == 'x') {
    complete_ = true;
  }

  // if we see a completion marker, first look for the completion date
  // otherwise look for the priority
  State loop_state{complete_ ? kDateCompleted : kPriority};

  const uint8_t delim     = ' ';
  ssize_t       start_pos = rawinput.find_first_not_of(delim, complete_ ? 1 : 0);
  ssize_t       delim_pos = rawinput.find_first_of(delim, start_pos);

  while (string::npos != start_pos || string::npos != delim_pos) {
    ssize_t          end_pos{delim_pos == string::npos ? rawinput.length() : delim_pos};
    ssize_t          val_len{end_pos - start_pos};
    std::string_view val{&rawinput.at(start_pos), val_len};
    // string val = rawinput.substr(start_pos, end_pos);

    ProcessWord(val, loop_state);
    start_pos = rawinput.find_first_not_of(delim, delim_pos);
    delim_pos = rawinput.find_first_of(delim, start_pos);
  }

  //PrintString();
}

auto Item::ProcessWord(const string_view val, Item::State& loop_state) -> void {
  switch (loop_state) {
    case kDateCompleted:
      loop_state = kPriority;
      if (ProcessDate(val, date_completed_)) {
        break;
      }
    case kPriority:
      loop_state = kDateAdded;
      // Check for priority
      if (val.length() == 3 && val[0] == '(' && val[2] == ')') {
        priority_ = val[1];
        // cout << rawinput << '\n';
        break;
      }
    case kDateAdded:
      loop_state = kBody;
      if (ProcessDate(val, date_added_)) {
        break;
      }
    case kBody:
      ProcessBody(val);
      break;
  }
}

auto Item::ProcessBody(const std::string_view item) -> void {
  switch (item.at(0)) {
    case '@': {
      string_view ctx{&item.at(1), item.length() - 1};
      if (!ContainsItem(contexts_, ctx)) {
        contexts_.emplace_back(ctx);
      }
      break;
    }
    case '+': {
      string_view tag{&item.at(1), item.length() - 1};
      if (!ContainsItem(tags_, tag)) {
        tags_.emplace_back(tag);
      }
      break;
    }
    default:
      auto colon_pos = item.find(':');
      if (colon_pos != string::npos) {
        auto key = item.substr(0, colon_pos);
        auto val = item.substr(colon_pos + 1);
        extensions_.emplace_back(key, val);
      }
  }
}

auto Item::ProcessDate(const std::string_view val, string& target_date) -> bool {
  if (val.length() == 10 && val[0] <= '9' && val[0] >= '0' && val[1] <= '9' && val[1] >= '0' && val[2] <= '9' &&
      val[2] >= '0' && val[3] <= '9' && val[3] >= '0' && val[4] == '-' && val[5] <= '1' && val[5] >= '0' &&
      val[6] <= '9' && val[6] >= '0' && val[7] == '-' && val[8] <= '3' && val[8] >= '0' && val[9] <= '9' &&
      val[9] >= '0') {
    target_date = val;
    return true;
  }

  return false;
}

auto Item::PrintString() -> void {
  cout << "raw: " << raw_ << '\n';
  cout << "complete: " << complete_ << "\n";
  cout << "date_completed: " << date_completed_ << "\n";
  cout << "priority: " << priority_ << '\n';
  cout << "date_added: " << date_added_ << "\n";

  cout << "contexts: ";
  std::copy(contexts_.begin(), contexts_.end(), std::ostream_iterator<string>(cout, " "));
  cout << '\n';

  cout << "tags: ";
  std::copy(tags_.begin(), tags_.end(), std::ostream_iterator<string>(cout, " "));
  cout << "\n";

  cout << "extensions: ";
  for (auto& p : extensions_) {
    cout << p.first << ":" << p.second << " ";
  }
  cout << "\n\n";
}

auto Item::raw() const -> string {
  return raw_;
}

auto Item::complete() const -> bool {
  return complete_;
}

auto Item::priority() const -> char {
  return priority_;
}

auto Item::contexts() const -> vector<string> {
  return contexts_;
}

auto Item::tags() const -> vector<string> {
  return tags_;
}

auto Item::date_completed() const -> string {
  return date_completed_;
}

auto Item::date_added() const -> string {
  return date_added_;
}

auto Item::extensions() const -> Extensions {
  return extensions_;
}
