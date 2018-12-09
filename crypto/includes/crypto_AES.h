/* Crypto_AES.h
 *
 *  Created on: Nov 17, 2013
 *      Author: lynn

	//sample use
	Crypto_AES myCrypto("I Like Rollos   "); //key must be a multiple of 16 c
	string string1 = "test string";			 //will be padded out to multiples of 32 chars
	int len = string1.length();
	myCrypto.encrypt(string1);
	len = string1.length();					//for above will be 2*32 =64
	myCrypto.decrypt(string1);
 */

#ifndef CRYPTO_AES_H_
#define CRYPTO_AES_H_
#include <string>
#include "../COMPLEXITY_TO_AVOID/Reindaal.h"
#include "../includes/crypto.h"

//keylength  can be 16, 24 or 32 bytes
const int KEYLENGTH = 16;

// blockSize  - The block size in bytes of this Rijndael (16, 24 or 32 bytes).
const int BLOCKSIZE = 16;

//helper enum
enum cryptType{ENCRYPT,DECRYPT};

class Crypto_AES: public Crypto
{
private:
	//does the encrypt/decrypt heavy lifting
	Reindaal  reindaal;

	//common code for actual encryption
	bool crypt(std::string &myData, cryptType myCryptType);

public:
	//used to see what went wrong 
	//when encrypting/decrypting
	int getLastError();

	//construct with a key of KEYLENGTH
	Crypto_AES(char *pKey);
	virtual ~Crypto_AES(void);

	//pass in a plaintext unencrypted string, its encrypted to unsigned char (binary) and 
	//then converted to a Hex string via HexHelper::CharStr2HexStr
	//doubles original string size, there are more efficient ways to do this 
	//returns true on success, false otherwise
	bool encrypt(std::string &myDecryptedData);

	//pass in an encrypted hex string, its converted to unsigned char (binary) via 
	//HexHelper::HexStr2CharStrand and then decrypted to original plaintext string 
	//returns true on success, false otherwise
	bool decrypt(std::string &myEncryptedData);
};


#endif /*  CRYPTO_AES_H_ */



