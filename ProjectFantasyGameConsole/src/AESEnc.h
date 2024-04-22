#pragma once
#include <rijndael.h>
#include <modes.h>
#include <cryptlib.h>
#include <osrng.h>
#include <vector>

// Aes encryption using CryptoPP (open src)
class AESEnc
{
public:
	std::vector<unsigned char> EncryptOFB(std::vector<unsigned char> in)
	{
		using namespace CryptoPP;
		std::vector<unsigned char> ret;
		auto Encrypt = [&](const std::initializer_list<unsigned char> key,
			const std::initializer_list<unsigned char> iv) {

				if (!key.size())
					return false; // Invalid key or key size
				try
				{
					OFB_Mode<AES>::Encryption e;
					e.SetKeyWithIV(key.begin(), AES::DEFAULT_KEYLENGTH, iv.begin(), AES::BLOCKSIZE);
					AES::Encryption aesEncryption(key.begin(), AES::DEFAULT_KEYLENGTH);
					OFB_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv.begin());
					VectorSource encryptor(in, true,
						new StreamTransformationFilter(cbcEncryption,
							new VectorSink(ret)
						)
					);
					StreamTransformationFilter filter(e);
					filter.Put((const byte*)in.data(), in.size());
					filter.MessageEnd();

					ret.resize(filter.MaxRetrievable());
					filter.Get(ret.data(), ret.size());
				}
				catch (const CryptoPP::Exception& e)
				{
					// Error
					ret.clear();
				}
			};
		Encrypt({
			0x1A, 0x4F, 0x8B, 0xE2, 0x34, 0x7D, 0x9C, 0x5E,
			0x70, 0xB6, 0x2D, 0xF9, 0xC3, 0x6A, 0x81, 0xD5
			}, {
			0x3E, 0x91, 0x5B, 0xF4, 0x62, 0xAF, 0x78, 0xCD,
			0x4A, 0xE7, 0x1D, 0x8F, 0x25, 0xD9, 0x6C, 0xB0
			});
		if (ret.size())
			return ret;
		else
			return std::vector<unsigned char>();
	}
	std::vector<unsigned char> DecryptOFB(std::vector<unsigned char> in)
	{
		using namespace CryptoPP;
		std::vector< unsigned char> ret;
		auto UI = [&](const std::initializer_list<unsigned char> key,
			const std::initializer_list<unsigned char> iv) {

				if (!key.size())
					return false; // Invalid key or key size
				try
				{
					OFB_Mode<AES>::Decryption d;
					d.SetKeyWithIV(key.begin(), AES::DEFAULT_KEYLENGTH, iv.begin(), AES::BLOCKSIZE);
					AES::Decryption aesDecryption(key.begin(), AES::DEFAULT_KEYLENGTH);
					OFB_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv.begin());
					VectorSource encryptor(in, true,
						new StreamTransformationFilter(cbcDecryption,
							new VectorSink(ret)
						)
					);
					StreamTransformationFilter filter(d);
					filter.Put((const byte*)in.data(), in.size());
					filter.MessageEnd();

					ret.resize(filter.MaxRetrievable());
					filter.Get(ret.data(), ret.size());
				}
				catch (const CryptoPP::Exception& e)
				{
					// Error
					ret.clear();
				}


			};
		UI({
			0x1A, 0x4F, 0x8B, 0xE2, 0x34, 0x7D, 0x9C, 0x5E,
			0x70, 0xB6, 0x2D, 0xF9, 0xC3, 0x6A, 0x81, 0xD5
			}, {
			0x3E, 0x91, 0x5B, 0xF4, 0x62, 0xAF, 0x78, 0xCD,
			0x4A, 0xE7, 0x1D, 0x8F, 0x25, 0xD9, 0x6C, 0xB0
			});
		if (ret.size())
			return ret;
		else
			return std::vector<unsigned char>();
	}
};

