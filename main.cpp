#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void log(const string &text) {
  ofstream data("data.txt", ios::app);
  if (data.is_open()) {
    data << text;
  } else {
    cout << "Failed to open file.";
  }
}

int main() {
  log("Starting the log...\n");

  return 0;
}
