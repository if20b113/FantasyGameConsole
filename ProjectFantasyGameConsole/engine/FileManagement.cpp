#include <fstream>
#include <sstream>

#include "FileManagement.hpp"

namespace FantasyGameEngine {

    bool write_text_to_file(const std::string& file_name, const std::string& content)
    {
        std::ofstream file(file_name);
        if (!file.is_open()) return false;

        file << content;
        file.close();

        return true;
    }

    std::string read_text_from_file(const std::string& file_name)
    {
        std::ifstream file(file_name);
        if (!file.is_open()) return {};

        std::stringstream result;
        std::string line;

        while (getline(file, line))
            result << line << '\n';

        file.close();

        return result.str();
    }

    bool write_data_to_file(const std::string& file_name, const char* data, std::size_t len)
    {
        std::ofstream file(file_name, std::ios::binary);
        if (!file.is_open()) return false;

        file.write(data, len);
        file.close();

        return true;
    }

    std::unique_ptr<char[]> read_data_from_file(const std::string& file_name)
    {
        std::ifstream file(file_name, std::ios::in | std::ios::binary | std::ios::ate);
        if (!file.is_open()) return std::unique_ptr<char[]>(nullptr);
        
        auto size = file.tellg();
        std::unique_ptr<char[]> result(new char[size]);
        file.seekg(0, std::ios::beg);
        file.read(result.get(), size);
        file.close();
        
        return result;
    }
}