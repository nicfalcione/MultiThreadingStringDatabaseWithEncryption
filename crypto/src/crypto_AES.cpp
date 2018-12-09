/* Crypto_AES.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: lynn
 */

#include <string.h>
#include <cmath>
#include <assert.h>

#include "../includes/crypto_AES.h"
#include "../includes/HexHelper.h"

const int KEY_SIZE_MULTIPLE16= 16;
const int KEY_SIZE_MULTIPLE24= 24;
const int KEY_SIZE_MULTIPLE32= 32;

Crypto_AES::Crypto_AES(char *pmKey): Crypto(pmKey)
{

}


Crypto_AES::~Crypto_AES(void)
{

}

bool Crypto_AES::crypt(std::string &myData, cryptType myCryptType){

	if (!pKey)
		return false;

	//when converting to hex buffer sizes need to grow
	//this multiplier handles that
	int multForHex=1;
	if (myCryptType == DECRYPT)
		multForHex = 2;

	//temps for encrypting
	char szDataInput[BLOCKSIZE*2+1];
	char szDataIntermediate[BLOCKSIZE+1];
	char szOut[BLOCKSIZE*2 +1];

	memset(szDataInput,0,BLOCKSIZE*2+1);
	memset(szDataIntermediate,0,BLOCKSIZE+1);
	memset(szOut,0,BLOCKSIZE*2+1);

	//need a key
	reindaal.MakeKey(pKey, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", KEYLENGTH, BLOCKSIZE);

	//how big is string to encrypt?
	int lenDecryptedData = myData.size();

	//are there any leftover chars that need padding out to BLOCKSIZE?
	int exrtraChars= lenDecryptedData%(BLOCKSIZE*2);
	if (exrtraChars != 0)
		lenDecryptedData +=  BLOCKSIZE*2 - lenDecryptedData%(BLOCKSIZE*2);

	//allocate with pads (should be RAII)
	char *p = new char[lenDecryptedData +1];
	memset(p,0,lenDecryptedData + 1);
	std::copy(myData.begin(), myData.end(), p);
	
	//clear
	myData.clear();

	//how many blocks
	double numblocks = floor(lenDecryptedData/(BLOCKSIZE*multForHex));
	char *pStart=p;
	for (int i = 0; i < numblocks; ++i) {
		strncpy(szDataInput, pStart, BLOCKSIZE*multForHex);
		pStart +=BLOCKSIZE*multForHex;
		if (myCryptType == DECRYPT){
			memset(szOut,0,BLOCKSIZE*2+1);
			HexHelper::HexStr2CharStr(szDataInput , (unsigned char*)szDataIntermediate, BLOCKSIZE);
			reindaal.DecryptBlock(szDataIntermediate, szOut);
		}
		else{
			reindaal.EncryptBlock(szDataInput, szDataIntermediate);
			HexHelper::CharStr2HexStr((unsigned char*)szDataIntermediate, szOut, BLOCKSIZE);
		}
		myData +=szOut;
	}
	
	//tidy up (should really be RAII)
	if (p)
		delete [] p;

	return true;
}


bool Crypto_AES::encrypt(std::string &myData){
	return crypt(myData, ENCRYPT);
}
bool Crypto_AES::decrypt(std::string &myData){
	return crypt(myData, DECRYPT);
}

