#ifndef STRINGTOOLS_HPP
#define STRINGTOOLS_HPP

#include <string>
#include <vector>

// Helper criado por mim para manipular string
using namespace std;

class StringTools {
   public:
    string trim(const string& str);
    vector<string> split(const string& str, const string& splitter);
    string toLowerCase(const string& str);
};

#endif  // TEXTPROCESSOR_H
