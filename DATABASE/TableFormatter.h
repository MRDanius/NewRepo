//#pragma once
//#include <string>
//#include <vector>
//#include <sstream>
//
//class TableFormatter {
//public:
//    // Ôîðìàòèðóåò äâóìåðíûé âåêòîð ñòðîê â îòôîðìàòèðîâàííóþ ASCII-òàáëèöó
//    static std::string format(const std::vector<std::vector<std::string>>& rows);
//};

// TableFormatter.h
#pragma once
#include <string>
#include <vector>
#include <sstream>

class TableFormatter {
public:
    static std::string format(const std::vector<std::vector<std::string>>& rows);
};
