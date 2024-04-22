#pragma once
#include <vector>
class MemoryData final
{
	// Used to encode anything into a char vector (and back)
private:
	std::vector< unsigned char > m_Data;
	size_t rPos;
	size_t wPos;

	bool ReadFromMemory(void* pBuffer, size_t const outSize)
	{
		if (outSize
			&& (wPos > rPos ? wPos - rPos : 0) >= outSize) // The remaining size has to be equal or larger than what we are asking for
		{
			::memcpy(pBuffer, &m_Data.at(rPos), outSize);
			rPos += outSize;
			return true;
		}
		return false;
	}
public:
	MemoryData()
	{
		Reset();
	}
	std::vector< unsigned char >& GetData()
	{
		return m_Data;
	}
	void Reset()
	{
		m_Data.clear();
		m_Data.reserve(256);
		m_Data.resize(0);
		rPos = 0;
		wPos = 0;
	}
	void AdjustPositions() // Use if your data was modified and changed without the class' knowledge
	{
		rPos = 0;
		wPos = m_Data.size();
	}
	template< typename T >
	void PushDataToVec(T const& input)
	{
		size_t const inSize = sizeof(T);
		if (0 < inSize)
		{
			m_Data.resize(wPos + inSize);
			::memcpy(&m_Data.at(wPos), (void const*)&input, inSize);
			wPos += inSize;
		}
	}
	template < typename T >
	bool ReadDataFromVec(T& outVal)
	{
		return ReadFromMemory(&outVal, sizeof(T));
	}
};

