#pragma once
#include <string>
#include <vector>
#include "../../crypto/includes/crypto.h"
#include "string_data.h"

//Abstract Base Class
//A generic store and load base class, extend to store/load to file, network, web, string, etc.
//provides base encryption services depending on whether a Crypto object is passed as part of constructor
class DataStore
{
private:
	Crypto* myCrypto;

protected:
	//ensures data is encrypted when stored
	//will encrypt/decrypt if myCrypto is not null
	//if myCrypto is null will store data in the clear
	//think about what this means for the implementation of the following 2 functions
	bool decrypt(std::string &myString);
	bool encrypt(std::string &myString);

public:
	//force derived classes to implement load and store as appropriate
	virtual bool load(std::vector<String_Data> &myVector)=0;
	virtual bool save(std::vector<String_Data> &myVector)=0;

	//pass in a crypto object and it will be used to encrypt 
	//data that is loaded or saved, otherwise data is stored in the clear
	DataStore(Crypto *pCrypt = 0);
	
	//please do not delete any crypto pointers that were passed
	//to this object, let the object creator manage them
	virtual ~DataStore(void);
};

