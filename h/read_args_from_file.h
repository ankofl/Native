#pragma once
#include "../h/answer_utils.h"

inline bool read_args_from_file(const std::string& filepath, std::vector<std::string>& args) {
    std::ifstream file(filepath); // ��������� ���� ��� ������
    args.clear();

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
        //answer_clear();
    }
    else {
        //answer_clear();
        answer_add(std::format("fail_open_file: < {} >\n", filepath));
    }
    return args.size() > 0;
}
