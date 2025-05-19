#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // ��� ������������� accumulate

// ����� ��� �������������� ������ � ������������ ������� �������
class TableFormatter {
public:
    // ������������ ����������� ������ ������� �� ������ ���������� � ������
    static std::vector<int> calculateColumnWidths(
        const std::vector<std::string>& headers,     // ��������� �������
        const std::vector<std::vector<std::string>>& data  // ������ ������� (������)
    ) {
        std::vector<int> widths(headers.size(), 0); // �������������� ������ ������

        // 1. ������������ ������ �� ����������
        for (size_t i = 0; i < headers.size(); ++i) {
            widths[i] = static_cast<int>(headers[i].length());
        }

        // 2. ��������� ������ �� ������
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                if (i < widths.size()) {
                    widths[i] = std::max(
                        widths[i],
                        static_cast<int>(row[i].length())
                    );
                }
            }
        }

        // 3. ��������� ������� (4 ������� � ������ �������)
        for (auto& w : widths) {
            w += 4;
        }

        return widths;
    }
};