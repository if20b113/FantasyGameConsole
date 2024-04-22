#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include <mutex>
class FileIO // Reads and saves data to files
{
private:
	class Mutex 
	{
	public:
		Mutex() { lock(); }
		~Mutex() { unlock(); }

		void lock() 
		{
			mutex.lock();
		}

		void unlock() 
		{
			mutex.unlock();
		}

	private:
		std::mutex mutex;
	};
public:
	bool SaveSaveFile(int& saveFile, std::vector<unsigned char> const & saveData)
	{
		Mutex mute;
		if (saveFile <= 0 || saveFile > 3)
		{
			saveFile = 1;
		}
		if (saveData.empty())
		{
			return false;
		}

		std::ofstream file;
		//std::wstring fileName(L"C:\\TetrisSaveData\\TetrisSave.file");
		//fileName += saveFile;
		// Open in binary mode, overwrite
		file.open("TetrisSave.file", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
 		if (file.is_open())
		{
			file.write((const char*)saveData.data(), (std::streamsize)saveData.size());
			file.close();
			return true;
		}
		else
		{
			if (file.fail()) 
			{
				std::cerr << "Error writing to file: " << std::strerror(errno) << std::endl;
			}
			file.close();
			return false;
		}
		

	}

	bool ReadSaveFile(int& saveFile, std::vector<unsigned char>& outSaveData)
	{
		Mutex mute;
		if (saveFile <= 0 || saveFile > 3)
		{
			saveFile = 1;
		}

		std::ifstream file;
		std::wstring fileName(L"F:\\FantasyGameConsole\\ProjectFantasyGameConsole\\build\\src\\Release\\TetrisSave.save");
		//fileName += saveFile;
		// Open in binary mode, overwrite
		file.open("TetrisSave.file", std::ios_base::binary);
		auto size = std::filesystem::file_size("TetrisSave.file");
		if (file.is_open())
		{
			file.seekg(0, std::ios::beg); // Move the position back to the beginning of the file
			outSaveData.resize(size);
			outSaveData.reserve(size);

			file.read((char*)outSaveData.data(), size); // read entire file size
			file.close();
			return true;
		}
		else
		{
			if (file.fail())
			{
				std::cerr << "Error writing to file: " << std::strerror(errno) << std::endl;
			}
			file.close();
			return false;
		}
	}
};

