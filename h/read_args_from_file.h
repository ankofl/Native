#pragma once
#include "../h/answer_utils.h"

inline bool read_args_from_file(const std::string& filepath, std::vector<std::string>& args) {
    std::ifstream file(filepath); // Открываем файл для чтения
    args.clear();

    if (file.is_open()) {
        std::string line;
        // Читаем всю строку из файла
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string word;
            // Разделяем строку по пробелам и добавляем слова в вектор
            while (iss >> word) {
                args.push_back(word);
            }
        }
        file.close(); // Закрываем файл
        //answer_clear();
    }
    else {
        //answer_clear();
        answer_add(std::format("fail_open_file: < {} >\n", filepath));
    }
    return args.size() > 0;
}
