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
  Item::State loop_state{complete_ ? kDateCompleted : kPriority};

  const uint8_t delim = ' ';
  ssize_t start_pos = rawinput.find_first_not_of(delim, complete_ ? 1 : 0);
  ssize_t delim_pos = rawinput.find_first_of(delim, start_pos);

  while (string::npos != start_pos || string::npos != delim_pos) {
    ssize_t end_pos{delim_pos == string::npos ? rawinput.length() : delim_pos};
    ssize_t val_len{end_pos - start_pos};
    std::string_view val{&rawinput.at(start_pos), val_len};
    // string val = rawinput.substr(start_pos, end_pos);

    process_word(val, loop_state);
    start_pos = rawinput.find_first_not_of(delim, delim_pos);
    delim_pos = rawinput.find_first_of(delim, start_pos);
  }

  print_string();
}

void Item::process_word(const string_view val,
                                Item::State &loop_state) {
  switch (loop_state) {
  case kDateCompleted:
    loop_state = kPriority;
    if (process_date(val, date_completed_)) {
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
    if (process_date(val, date_added_)) {
      break;
    }
  case kBody:
    process_body(val);
    break;
  }
}

void Item::print_string() {
  cout << "raw: " << raw_ << '\n';
  cout << "complete: " << complete_ << "\n";
  cout << "date_completed: " << date_completed_ << "\n";
  cout << "priority: " << priority_ << '\n';
  cout << "date_added: " << date_added_ << "\n";
  cout << "contexts: ";
  std::copy(contexts_.begin(), contexts_.end(),
            std::ostream_iterator<string>(cout, " "));
  cout << '\n';
  cout << "tags: ";
  std::copy(tags_.begin(), tags_.end(),
            std::ostream_iterator<string>(cout, " "));
  cout << "\n\n";
}

void Item::process_body(const std::string_view val) {
  switch (val.at(0)) {
  case '@':
    contexts_.emplace_back(string_view{&val.at(1), val.length() - 1});
    break;
  case '+':
    tags_.emplace_back(string_view{&val.at(1), val.length() - 1 });
    break;
  }
}

bool Item::process_date(const std::string_view val, string &target_date) {

  if (val.length() == 10 && val[0] <= '9' && val[0] >= '0' && val[1] <= '9' &&
      val[1] >= '0' && val[2] <= '9' && val[2] >= '0' && val[3] <= '9' &&
      val[3] >= '0' && val[4] == '-' && val[5] <= '1' && val[5] >= '0' &&
      val[6] <= '9' && val[6] >= '0' && val[7] == '-' && val[8] <= '3' &&
      val[8] >= '0' && val[9] <= '9' && val[9] >= '0') {

    target_date = val;
    return true;
  }

  return false;
}

string Item::raw() { return raw_; }
bool Item::complete() { return complete_; };
char Item::priority() { return priority_; };
vector<string> Item::contexts() { return contexts_; };
vector<string> Item::tags() { return tags_; };
string Item::date_completed() { return date_completed_; };
string Item::date_added() { return date_added_; };
unordered_map<string, string> Item::extensions() { return extensions_; };
