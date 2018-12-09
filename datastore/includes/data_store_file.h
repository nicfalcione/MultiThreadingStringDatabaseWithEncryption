#pragma once
#include <iostream>
#include <vector>
#include "../includes/data_store.h"
#include "string_data.h"

//loads data from a file and saves it back to a file
//either in cleartext or encrypted depending on whether you pass it a 
//crypto object
class DataStore_File :
	public DataStore
{
public:
	//pass in a crypto object and it will be used to en/decrypt data
	//don't, and data stored in clear
	DataStore_File(std::string fileName, Crypto* crypto = 0);
	virtual ~DataStore_File(void);

	//load from file myFileName, if present, use the crypto object to decrypt 
	//returns true on success, false otherwise
	bool load(std::vector<String_Data> &myVector);

	//save to file myFileName, if present, use the crypto object to encrypt 
	//I extracted one entry of the vector at a time and then encrypted it
	//if crypto object present, saved this to disk and then sent a std::endl
	//so each entry is encrypted, but you can count the number of entries 
	//by the number of lines in the file
	//returns true on success, false otherwise
	bool save(std::vector<String_Data> &myVector);
private:
	bool openFile(std::fstream& myfile,const std::string& myFileName, std::ios_base::openmode mode=std::ios_base::in);
	void closeFile(std::fstream& myfile);

	std::string myFileName;
};

