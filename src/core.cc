#include <iostream>
#include <string>
#include "core.h"
using namespace std;

namespace ModuleCore {
  namespace Lines {
    string prompt(string str) {
      cout << str;
      
      string line;
      getline(cin, line);
      
      return line;
    }
    
    string forcePrompt(string str) {
      cout << str;
      string line;
      getline(cin, line);
      
      while (line.empty()) {
        cout << str;
        getline(cin, line);
      }
      
      return line;
    }
  }
}