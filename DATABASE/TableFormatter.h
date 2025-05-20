//#pragma once
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <numeric> // ��� ������������� accumulate
//
//// ����� ��� �������������� ������ � ������������ ������� �������
//class TableFormatter {
//public:
//    // ������������ ����������� ������ ������� �� ������ ���������� � ������
//    static std::vector<int> calculateColumnWidths(
//        const std::vector<std::string>& headers,     // ��������� �������
//        const std::vector<std::vector<std::string>>& data  // ������ ������� (������)
//    ) {
//        std::vector<int> widths(headers.size(), 0); // �������������� ������ ������
//
//        // 1. ������������ ������ �� ����������
//        for (size_t i = 0; i < headers.size(); ++i) {
//            widths[i] = static_cast<int>(headers[i].length());
//        }
//
//        // 2. ��������� ������ �� ������
//        for (const auto& row : data) {
//            for (size_t i = 0; i < row.size(); ++i) {
//                if (i < widths.size()) {
//                    widths[i] = std::max(
//                        widths[i],
//                        static_cast<int>(row[i].length())
//                    );
//                }
//            }
//        }
//
//        // 3. ��������� ������� (4 ������� � ������ �������)
//        for (auto& w : widths) {
//            w += 4;
//        }
//
//        return widths;
//    }
//};


#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
class TableFormatter {
public:
    // ��������� ��� ������������ ����� �������
    struct ColumnConfig {
        size_t width;
        bool isNumeric;
        std::string filterPattern;
    };

    // ��������� ����� �������
    static void printHeader(const std::vector<ColumnConfig>& columns) {
        std::cout << "\n";
        for (const auto& col : columns) {
            std::cout << "| " << std::left << std::setw(col.width)
                << std::string(col.width - 2, '-') << " ";
        }
        std::cout << "|\n";
    }

    // �������������� ������ ������
    static std::string formatRow(
        const std::vector<std::string>& values,
        const std::vector<ColumnConfig>& columns
    ) {
        std::stringstream ss;
        for (size_t i = 0; i < values.size(); ++i) {
            if (columns[i].isNumeric) {
                ss << "| " << std::right << std::setw(columns[i].width)
                    << values[i] << " ";
            }
            else {
                ss << "| " << std::left << std::setw(columns[i].width)
                    << values[i] << " ";
            }
        }
        ss << "|";
        return ss.str();
    }
};