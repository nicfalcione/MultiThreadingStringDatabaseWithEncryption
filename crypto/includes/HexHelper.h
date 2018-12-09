#pragma once
//this class is not meant for instantiation, just a static helper
class HexHelper
{
public:
	//converts from 1 byte binary to 2 byte hex
	static void Char2Hex(unsigned char ch, char* szHex);
	static void Hex2Char(char const* szHex, unsigned char& rch);
	static void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);
	static void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);

private:
	HexHelper(void);
	~HexHelper(void);
};

