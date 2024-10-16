#include "h/read_args_from_file.h"
#include "cpp/boolean_mesh_1_mesh_2.cpp"
#include "cpp/union_meshes.cpp"

int main() {
    std::vector<std::string> args; // Читаем параметры из файла    
    if (read_args_from_file(path_data, args)) {
        if (args[0] == start_boolean_mesh_1_mesh_2 && args.size() == 5) {
            boolean_mesh_1_mesh_2(
                args[1],            // Первый аргумент как строка
                args[2],            // Второй аргумент как строка
                std::stoull(args[3]), // Третий аргумент как size_t
                args[4]);           // Четвёртый аргумент как строка
        }
        else if (args[0] == start_union_meshes && args.size() == 3) {
            union_meshes(
                args[1], // Путь к папке с .off файлами
                args[2]);// Путь сохранения объединённого .off файла
        }
    }

    return 0;
}
