/*
 * Data_store.cpp file
 * Author: Nic Falcione
 * Date:   11/19/18
 */
#include <string>
#include <vector>
#include "../includes/data_store.h"

//Abstract Base Class
//A generic store and load base class, extend to store/load to file, network, web, string, etc.
//provides base encryption services depending on whether a Crypto object is passed as part of constructor

//ensures data is encrypted when stored
//will encrypt/decrypt if myCrypto is not null
//if myCrypto is null will store data in the clear
//think about what this means for the implementation of the following 2 functions
bool DataStore::decrypt(std::string &myString) {
	if (myCrypto == 0) {
		return false;
	}
	return myCrypto->decrypt(myString);
}

bool DataStore::encrypt(std::string &myString) {
	if (myCrypto == 0) {
		return false;
	}
	return myCrypto->encrypt(myString);
}

//pass in a crypto object and it will be used to encrypt
//data that is loaded or saved, otherwise data is stored in the clear
DataStore::DataStore(Crypto *pCrypt) {
	myCrypto = pCrypt;
}

//please do not delete any crypto pointers that were passed
//to this object, let the object creator manage them
DataStore::~DataStore(void) {
}

