#include <vex.h>
#include <string.h>
#include <sstream>
#include <vector>
#include "micro/MTypeConvert.h"

// convertToString: to std::string,                 from int / double / char
// convertToInt: to int,                            from std::string
// stringJoin: to std::string,                      from std::vector<int> / std::vector<std::string>
// stringSplitToInt: to vector<int>,                from std::string
// stringSplitToString: to vector<std::string>,     from std::string

std::string MTypeConvert::convertToString(int toConvert) {
  std::ostringstream strstream;
  strstream << toConvert;
  return strstream.str();
}

std::string MTypeConvert::convertToString(double toConvert) {
  std::ostringstream strstream;
  strstream << toConvert;
  return strstream.str();
}

std::string MTypeConvert::convertToString(char toConvert) {
  std::string s(1, toConvert);
  return s;
}

int MTypeConvert::convertToInt(std::string integer) {
  return atoi(integer.c_str());
}

std::string MTypeConvert::stringJoin(std::vector<int> vect, std::string separator) {
    std::string str = "";
		for(short i = 0; i < vect.size(); i++) str += convertToString(vect.at(i)) + separator ;
		return str;
}

std::string MTypeConvert::stringJoin(std::vector<std::string> vect, std::string separator) {
  std::string str = "";
	for(short i = 0; i < vect.size(); i++) str += vect.at(i) + separator ;
	return str;
}

std::vector<int> MTypeConvert::stringSplitToInt(std::string s, std::string separator) {
	std::string tkn;
	std::vector<int> returnData;

	std::stringstream ss(s);
	for(int i; ss >> i;) {
		returnData.push_back(i);
		if (convertToString(ss.peek()) == separator) ss.ignore();
	}
	return returnData;
}

std::vector<std::string> MTypeConvert::stringSplitToString(std::string s, std::string separator) {
	std::string tkn;
	std::vector<std::string> returnData;

	std::stringstream ss(s);
	for(std::string i; ss >> i;) {
		returnData.push_back(i);
		if (convertToString(ss.peek()) == separator) ss.ignore();
	}
	return returnData;
}
