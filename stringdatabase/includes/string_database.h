#pragma once
#include <string>
#include <vector>
#include <mutex>
#include "../../datastore/includes/string_data.h"
#include "../../datastore/includes/data_store_file.h"

class String_Database
{
private:
	std::mutex mutex;
	std::vector<String_Data> myStrings;
	std::vector<String_Data>::iterator  myStringsIter;

public:
	String_Database(void);
	~String_Database(void);

	//if not seen yet then add myString to myStrings
	//otherwise increment the count for myString
	void add(std::string &myString);

	//get number of times myString has been seen (or added with add)
	int getCount(std::string &myString);

	//clear the myStrings vector
	void clear();

	//load from datastore, returns 
	//false if myDataStore = 0
	//otherwise returns myDataStore->load results
	bool load(DataStore  *myDataStore);

	//save to datastore,returns 
	//false if myDataStore = 0
	//otherwise returns myDataStore->save results
	bool save(DataStore *myDataStore);
};

