//============================================================================
// Name        : MED_Tester.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <sstream>
#include <fstream>

#include "../datastore/includes/data_store.h"
#include "../datastore/includes/data_store_file.h"
#include "../stringdatabase/includes/string_database.h"
#include "../crypto/includes/crypto_AES.h"
#include "../crypto/includes/crypto.h"

using namespace std;

//I've provided some hints in the form of comments and commented out code
//use them if you wish

//global database object
String_Database myGlobalCache;

const string inFile = "../MED_Tester/input.txt";
const string outFile = "../MED_Tester/output.txt";

vector<thread> threads;

bool testSerialization(const std::string &MYFILE1, const std::string &MYFILE2,
		Crypto *pCrypto) {

	string love = "love";
	string love1 = "times";
	string love2 = "two";
	string love3 = "me";
	string love4 = "love";
	string love5 = "me";
	string love6 = "two";
	string love7 = "times";
	string s = "yayeehaw";
	myGlobalCache.add(love);
	myGlobalCache.add(love1);
	myGlobalCache.add(love2);
	myGlobalCache.add(love3);
	myGlobalCache.add(love4);
	myGlobalCache.add(love5);
	myGlobalCache.add(love6);
	myGlobalCache.add(love7);
	myGlobalCache.add(s);
	cout << "Adding to Cache\n";

	DataStore_File myDataStore_File1(MYFILE1, pCrypto);
	myGlobalCache.save(&myDataStore_File1);
	cout << "Saving to " << MYFILE1 << " from cache\n";

	//clear cache
	myGlobalCache.clear();
	cout << "Clearing Cache\n";

	//load it
	myGlobalCache.load(&myDataStore_File1);
	std::cout << "Loading from file " + MYFILE1 + " \n";

	//save to a different file
	DataStore_File myDataStore_File2(MYFILE2, pCrypto);
	myGlobalCache.save(&myDataStore_File2);

	std::cout << "Saving to file " + MYFILE2 + " \n";

	//I use my own objects here to compare the files
	return true;
}

void runThis() {
	string love = "love";
	string love1 = "times";
	string love2 = "two";
	string love3 = "me";
	string love4 = "love";
	string love5 = "me";
	string love6 = "two";
	string love7 = "times";
	string s = "yayeehaw";
	myGlobalCache.add(love);
	myGlobalCache.add(love1);
	myGlobalCache.add(love2);
	myGlobalCache.add(love3);
	myGlobalCache.add(love4);
	myGlobalCache.add(love5);
	myGlobalCache.add(love6);
	myGlobalCache.add(love7);
	myGlobalCache.add(s);
}

bool compareFiles() {
	ifstream file1;
	ifstream file2;
	file1.open(inFile);
	file2.open(outFile);

	if (!file1.is_open() || !file2.is_open()) {
		return false;
	}

	string line1;
	string line2;
	while (!file1.eof() || !file2.eof()) {
		getline(file1, line1);
		getline(file2, line2);

		if (line1 != line2) {
			return false;
		}
	}

	file1.close();
	file2.close();
	return true;
}

int main() {

	//I created and ran a bunch(20) of threads that added different strings to a string_database instance
	for (int i = 0; i < 20; i++) {
		threads.push_back(thread(runThis));
	}

	for (auto& thread : threads) {
		thread.join();
	}

	//Then I waited for all of them to finish so my program did not crash

	//Then I went through my string_database instance and made sure that it held the correct data

	//then I tested  serialization
	//first without encryption, 
	testSerialization(inFile, outFile, 0);

	if (compareFiles()) {
		cout << "File 1 and File 2 are equivalent without encryption!" << endl;
	} else {
		cout
				<< "Test failed, files not equivalent after load and save without encryption"
				<< endl;
	}

	//then with
	Crypto_AES myCrypto("I Like Rollos   ");
	testSerialization(inFile, outFile, &myCrypto);
	if (compareFiles()) {
		cout << "File 1 and File 2 are equivalent with encryption!" << endl;
	} else {
		cout
				<< "Test failed, files not equivalent after load and save with encryption"
				<< endl;
	}
}
