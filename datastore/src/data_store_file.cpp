/*
 * data_store_file.cpp file
 * Author: Nic Falcione
 * Date:   11/19/18
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <exception>

#include "../includes/data_store_file.h"
#include "../includes/data_store.h"

using namespace std;

//loads data from a file and saves it back to a file
//either in cleartext or encrypted depending on whether you pass it a
//crypto object
//pass in a crypto object and it will be used to en/decrypt data
//don't, and data stored in clear
DataStore_File::DataStore_File(std::string fileName, Crypto* crypto) :
		DataStore(crypto) {
	myFileName = fileName;
}

DataStore_File::~DataStore_File(void) {
}

//load from file myFileName, if present, use the crypto object to decrypt
//returns true on success, false otherwise
bool DataStore_File::load(std::vector<String_Data> &myVector) {
	ifstream file;

	file.open(myFileName.c_str());
	if (!file.is_open()) {
		return false;
	}

	string data = "";
	string line;
	int count = 0;
	while (!file.eof()) {
		String_Data sd(data, count);
		getline(file, line);
		if (line == "") {
			break;
		}
		DataStore::decrypt(line);
		sd.parseData(line, data, count);
		String_Data s(data, count);
		myVector.push_back(s);
	}

	file.close();
	return true;
}

//save to file myFileName, if present, use the crypto object to encrypt
//I extracted one entry of the vector at a time and then encrypted it
//if crypto object present, saved this to disk and then sent a std::endl
//so each entry is encrypted, but you can count the number of entries
//by the number of lines in the file
//returns true on success, false otherwise
bool DataStore_File::save(std::vector<String_Data> &myVector) {
	ofstream file;
	file.open(myFileName);
	if (!file.is_open()) {
		return false;
	}

	string data = "";
	for (unsigned int i = 0; i < myVector.size(); ++i) {
		data = myVector[i].serialize();
		DataStore::encrypt(data);
		file << data << endl;
	}

	file.close();
	return true;
}

bool DataStore_File::openFile(std::fstream& myfile,
		const std::string& myFileName, std::ios_base::openmode mode) {
	if (!myfile.good()) {
		return false;
	}
	myfile.open(myFileName.c_str(), mode);
	if (myfile.is_open()) {
		return true;
	}
	return false;
}

void DataStore_File::closeFile(std::fstream& myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}
