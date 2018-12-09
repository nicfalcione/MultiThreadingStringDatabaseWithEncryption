#include <string.h>
#include "../includes/crypto.h"

const int KEY_SIZE_16 = 16;
const int KEY_SIZE_24 = 24;
const int KEY_SIZE_32 = 32;

Crypto::Crypto(char *pmKey): iLastError(ERROR_NO_ERROR),pKey(0)
{
	//make a copy of pKey;
	if (pmKey)
	{
		//how long
		int keyLen = strlen(pmKey);

		//make sure either 16, 24 or 32 bits
		if ( (keyLen%KEY_SIZE_16 != 0) && (keyLen%KEY_SIZE_24 != 0) && (keyLen%KEY_SIZE_32 != 0)){
			iLastError= ERROR_KEY_LENGTH_INVALID;
			return;
		}

		//danger here if throw an exception
		pKey = new char[keyLen +1];
		memset(pKey,0,keyLen +1);
		memcpy(pKey,pmKey,keyLen);
	}
	else
		iLastError = ERROR_NO_KEY_SET;
}


Crypto::~Crypto(void)
{
	if (pKey)
		delete [] pKey;
}
