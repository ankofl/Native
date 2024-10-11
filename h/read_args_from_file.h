#pragma once
#include "../h/answer_utils.h"

std::vector<std::string> read_args_from_file(const std::string& filepath) {
    std::ifstream file(filepath); // ��������� ���� ��� ������
    std::vector<std::string> args; // ������ ������ ��� �������� ����������

    if (file.is_open()) {
        std::string line;
        // ������ ��� ������ �� �����
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string word;
            // ��������� ������ �� �������� � ��������� ����� � ������
            while (iss >> word) {
                args.push_back(word);
            }
        }
        file.close(); // ��������� ����
        answer_clear();
    }
    else {
        answer_clear();
        answer_add(std::format("fail_open_file: < {} >\n", filepath));
    }
    return args;
}
