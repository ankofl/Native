#pragma once
#include "../h/answer_utils.h"

std::vector<std::string> read_args_from_file(const std::string& filepath) {
    std::ifstream file(filepath); // Открываем файл для чтения
    std::vector<std::string> args; // Создаём вектор для хранения аргументов

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
        answer_clear();
    }
    else {
        answer_clear();
        answer_add(std::format("fail_open_file: < {} >\n", filepath));
    }
    return args;
}
