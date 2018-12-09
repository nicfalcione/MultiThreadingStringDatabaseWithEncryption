#pragma once
#include <string>

//used to store string/count pairs
class String_Data
{
private:
	std::string data;
	int useCount;
	
	// overloaded assignment
	const String_Data &operator=(const String_Data &other);
public:
	//copy constructor, destructor
	//do not make this private or vector will not work
	//(push_back makes a copy)
	String_Data(const String_Data &other);

	//create
	String_Data(std::string data, int useCount=1);
	~String_Data(void);

	//how many times seen
	inline int getCount(){return useCount;}
	inline void increment(){useCount++;}

	//use for saving data to an external file
	//for example if data = "data 1" and useCount = 15
	//then serialize should return "data 1,15"
	std::string serialize();

	//compare
	bool operator==( const String_Data &ud); 

	//static helper function, parses data and usecount out of a string
	//so if myString = "data 1,15" when done data = "data 1" and useCount=15
	static bool parseData(std::string &myString, std::string &data, int &useCount);
};
