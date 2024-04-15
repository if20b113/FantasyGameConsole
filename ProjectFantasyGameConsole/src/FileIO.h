#pragma once
#include <fstream>
#include <vector>
class FileIO // Reads and saves data to files
{
public:
	bool SaveSaveFile(int& saveFile, std::vector<unsigned char> const & saveData)
	{
		if (saveFile <= 0 || saveFile > 3)
		{
			saveFile = 1;
		}
		if (saveData.empty())
		{
			return false;
		}

		std::fstream file;
		std::wstring fileName(L"TetrisSave");
		fileName += saveFile;
		// Open in binary mode, overwrite
		file.open(fileName.c_str(), std::ios_base::out | std::ios_base::trunc | std::ios_base::ate | std::ios_base::binary);
		if (!file.is_open())
		{
			file.write((const char*)saveData.at(0), (std::streamsize)saveData.size());
			file.close();
			return true;
		}
		else
		{
			return false;
		}

	}

	bool ReadSaveFile(int& saveFile, std::vector<unsigned char>& outSaveData)
	{
		if (saveFile <= 0 || saveFile > 3)
		{
			saveFile = 1;
		}

		std::fstream file;
		std::wstring fileName(L"TetrisSave");
		fileName += saveFile;
		// Open in binary mode, overwrite
		file.open(fileName.c_str(), std::ios_base::out | std::ios_base::trunc | std::ios_base::ate | std::ios_base::binary);
		if (!file.is_open())
		{
			file.read((char*)outSaveData.at(0), file.tellg()); // read entire file size
			file.close();
			return true;
		}
		else
		{
			return false;
		}
	}
};

