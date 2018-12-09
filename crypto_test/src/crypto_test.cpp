//============================================================================
// Name        : crypto_test.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "../../crypto/includes/crypto_AES.h"
using namespace std;

int main() {
	try
	{
		//string mkey = "I Like Rollos   ";
		char key[] = "I Like Rollos   ";
		char *pKey = &key[0];
		
		//create with a passphrase,
		//***** MUST BE 16 CHARS LONG, no more no less ******
		Crypto_AES myCrypto(pKey);

		//here is the string to encrypt
		std::string myString("I would like a peanut butter sandwich and then a cup of fine tea");
		cout<<"String to encrypt\t="<<myString<<endl;

		//encrypt it
		myCrypto.encrypt(myString);
		cout<<"Encrypted String\t="<<myString<<endl;

		//decrypt it
		myCrypto.decrypt(myString);
		cout<<"Decrypted String\t="<<myString<<endl;
	}
	catch(exception& roException)
	{
		cout << roException.what() << endl;
	}

	return 0;
}
