
#include "typedefs_std.h"
#include "read_args_from_file.h"
#include "boolean_mesh_1_mesh_2.cpp"
#include "answer_utils.h"

int main() {
    std::vector<std::string> args = read_args_from_file(path_data); // Читаем параметры из файла    

    // Проверяем, что вектор args содержит нужное количество параметров
    if (!args.empty() && args[0] == start_boolean_mesh_1_mesh_2 && args.size() == 5) {
        boolean_mesh_1_mesh_2(
            args[1],            // Первый аргумент как строка
            args[2],            // Второй аргумент как строка
            std::stoull(args[3]), // Третий аргумент как size_t
            args[4]);           // Четвёртый аргумент как строка
    }
    else {
        answer_add("incorrect_args");
    }

    return 0;
}
