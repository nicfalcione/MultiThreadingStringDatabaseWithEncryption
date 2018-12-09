#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include "../../datastore/includes/string_data.h"
#include "../../datastore/includes/data_store_file.h"
#include "../includes/string_database.h"

using namespace std;

String_Database::String_Database(void) {

}
String_Database::~String_Database(void) {

}

//if not seen yet then add myString to myStrings
//otherwise increment the count for myString
void String_Database::add(std::string &myString) {
	lock_guard<std::mutex> guard(mutex);
	for (unsigned int i = 0; i < myStrings.size(); i++) {
		int count = myStrings[i].getCount();
		String_Data sd(myString, count);
		if (myStrings[i] == sd) {
			myStrings[i].increment();
			return;
		}
	}
	String_Data sd(myString, 1);
	myStrings.push_back(sd);
}

//get number of times myString has been seen (or added with add)
int String_Database::getCount(std::string &myString) {
	lock_guard<std::mutex> guard(mutex);
	for (unsigned int i = 0; i < myStrings.size(); i++) {
		int count = myStrings[i].getCount();
		String_Data sd(myString, count);
		if (myStrings[i] == sd) {
			return myStrings[i].getCount();
		}
	}
	return 0;
}

//clear the myStrings vector
void String_Database::clear() {
	myStrings.clear();
}

//load from datastore, returns
//false if myDataStore = 0
//otherwise returns myDataStore->load results
bool String_Database::load(DataStore *myDataStore) {
	if (myDataStore == 0) {
		return false;
	}
	return myDataStore->load(myStrings);
}

//save to datastore,returns
//false if myDataStore = 0
//otherwise returns myDataStore->save results
bool String_Database::save(DataStore *myDataStore) {
	if (myDataStore == 0) {
		return false;
	}
	return myDataStore->save(myStrings);
}

