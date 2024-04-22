#pragma once
#include <iostream>
#include <array>
#include "MemoryData.h"
#include "FileIO.h"
#include "AESEnc.h"
class SaveData
{
private:
	std::vector< unsigned char > m_saveData;
	int saveFile{ 1 }; // 1-3
	void GameFieldToSaveStructure(std::array < std::array<int, 45>, 25> const& inField)
	{
		MemoryData mem;
		for (auto it : inField)
			for (int value : it)
				mem.PushDataToVec(value);
		m_saveData.reserve(mem.GetData().size());
		m_saveData.swap(mem.GetData());
	}
	bool SaveStructureToGameField(std::vector<unsigned char>& inData, std::array < std::array<int, 45>, 25>& outField)
	{
		MemoryData mem;
		mem.GetData().reserve(inData.size());
		mem.GetData().resize(inData.size());
		mem.GetData().swap(inData);
		mem.AdjustPositions();
		for (auto& it : outField)
			for (int& value : it)
				if (!mem.ReadDataFromVec(value)) // we read from position 0, so we dont have to read from reverse
					return false;// Error;
		return true;
	}
public:

	bool SaveFile(int& saveFile, std::array < std::array<int, 45>, 25> const& inField)
	{
		this->saveFile = saveFile;
		GameFieldToSaveStructure(inField);

		AESEnc enc;
		m_saveData = enc.EncryptOFB(m_saveData);
		if (m_saveData.empty())
		{
			return false; // No data is present
		}

		// Output (?) saved file to save file: %saveFile%
		FileIO fileIo;
		return fileIo.SaveSaveFile(saveFile, m_saveData);
	}

	bool LoadFile(int& saveFile, std::array < std::array<int, 45>, 25>& outField)
	{
		this->saveFile = saveFile;
		if (!m_saveData.empty())
		{
			m_saveData.clear();
		}

		// Output (?) saved file to save file: %saveFile%
		FileIO fileIo;
		if (!fileIo.ReadSaveFile(saveFile, m_saveData))
		{
			// something went wrong
			return false;
		}
		AESEnc enc;
		m_saveData = enc.DecryptOFB(m_saveData);
		return SaveStructureToGameField(m_saveData, outField);
	}
};

