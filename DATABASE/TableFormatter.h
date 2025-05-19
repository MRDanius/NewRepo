#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <numeric> // Для использования accumulate

// Класс для форматирования таблиц с динамической шириной колонок
class TableFormatter {
public:
    // Рассчитывает оптимальную ширину колонок на основе заголовков и данных
    static std::vector<int> calculateColumnWidths(
        const std::vector<std::string>& headers,     // Заголовки таблицы
        const std::vector<std::vector<std::string>>& data  // Данные таблицы (строки)
    ) {
        std::vector<int> widths(headers.size(), 0); // Инициализируем ширины нулями

        // 1. Рассчитываем ширину по заголовкам
        for (size_t i = 0; i < headers.size(); ++i) {
            widths[i] = static_cast<int>(headers[i].length());
        }

        // 2. Обновляем ширину по данным
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

        // 3. Добавляем отступы (4 пробела к каждой колонке)
        for (auto& w : widths) {
            w += 4;
        }

        return widths;
    }
};