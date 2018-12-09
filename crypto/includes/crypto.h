#ifndef CRYPTO_H_
#define CRYPTO_H_
#include <string>

//possible error conditions
//I know its not an enum and its not in constants.h
//this is another common programming technique
//the codes are with the header file where they are used
//not as safe as an enum since they can be any int 
const int SUCCESS					= 0;
const int ERROR_NO_ERROR 			= SUCCESS;
const int ERROR_KEY_LENGTH_INVALID	= SUCCESS - 1;
const int ERROR_NO_KEY_SET			= SUCCESS - 2;
const int ERROR_BUFFER_TOO_SMALL	= SUCCESS - 3;

//Abstract Base Class (ABC) so you cannot instantiate it
//serve as the basis for symmetric key encryption types AES, RC4, triple DES etc.
class Crypto
{
protected:
	int iLastError;
	char *pKey;

public:
	//indicates last error that occurred during 
	//encrypt/decrypt. iLastError holds the value
	//can be one of the consts above
	int getLastError();

	//key length 16 chars (excluding the \0)
	Crypto(char *pKey);
	virtual ~Crypto(void);

	virtual bool encrypt(std::string &myDecryptedData)=0;
	virtual bool decrypt(std::string &myEncryptedData)=0;
};

#endif /* CRYPTO_H_ */
