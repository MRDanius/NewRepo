// TableFormatter.cpp

#include "TableFormatter.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

// Эта функция преобразует набор строк в ровные колонки
std::string TableFormatter::format(const std::vector<std::vector<std::string>>& rows) {
    if (rows.empty()) return "";

    size_t cols = rows[0].size();
    std::vector<size_t> widths(cols, 0);

    // Вычисляем максимальную ширину каждого столбца
    for (const auto& row : rows) {
        for (size_t i = 0; i < cols; ++i) {
            if (row[i].length() > widths[i]) {
                widths[i] = row[i].length();
            }
        }
    }

    std::ostringstream oss;
    // Формируем строки
    for (const auto& row : rows) {
        for (size_t i = 0; i < cols; ++i) {
            oss << std::left << std::setw(widths[i] + 2) << row[i];
        }
        oss << "\n";
    }
    return oss.str();
}
