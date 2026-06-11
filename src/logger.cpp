#include "logger.hpp"

#include <fstream>
#include <iostream>

using namespace std;

void log(string &storage) {
  ofstream data("data.txt", ios::trunc);

  if (data.is_open()) {
    data << storage;
  } else {
    cout << "Failed to open file.";
  }
}
