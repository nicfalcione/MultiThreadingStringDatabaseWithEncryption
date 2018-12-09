#include <vector>
#include <sstream> 
#include <string>

#include "../includes/string_data.h"

using namespace std;

String_Data::String_Data(std::string data, int useCount): data(data),useCount(useCount)
{
}

//copy constructor
String_Data::String_Data(const String_Data &other){
	this->data = other.data;
	this->useCount = other.useCount;
}


String_Data::~String_Data(void)
{
}


bool String_Data::operator==( const String_Data &ud)
{
	return (data == ud.data);
} 


std::string String_Data::serialize(){
	return (std::string(data + "," + std::to_string(useCount)));
}

bool String_Data::parseData(std::string &myString, std::string &data, int &useCount){
	stringstream ss(myString);

	//get data
	if ( !ss.good() )
		return false;
	getline( ss, data, ',' );

	//get usecount
	if ( !ss.good() )
		return false;

	string tmpString;	
	getline( ss, tmpString, ',' );
	istringstream( tmpString)>>useCount;

	return true;
}
