#include "logger.hpp"

#include <fstream>
#include <iostream>

using namespace std;

void log(const string &text) {
  ofstream data("data.txt", ios::app);

  if (data.is_open()) {
    data << text;
  } else {
    cout << "Failed to open file.";
  }
}
