#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <memory>
#include <vector>

namespace FantasyGameEngine {

	bool write_text_to_file(const std::string& file_name, const std::string& content);
	std::string read_text_from_file(const std::string &file_name);

	bool write_data_to_file(const std::string& file_name, const char *data, int len);
	std::unique_ptr<char[]> read_data_from_file(const std::string& file_name);

	bool update_score(const std::string& score_file_name, const std::string& name, int score);
	std::vector<std::tuple<std::string, int, std::string>> get_scores(const std::string& score_file_name);
}

#endif