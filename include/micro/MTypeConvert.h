#include <string.h>
#include <sstream>
#include <vector>

// convertToString: to std::string,                 from int / double / char
// convertToInt: to int,                            from std::string
// stringJoin: to std::string,                      from std::vector<int> / std::vector<std::string>
// stringSplitToInt: to vector<int>,                from std::string
// stringSplitToString: to vector<std::string>,     from std::string

class MTypeConvert {
public: std::string convertToString(int toConvert);
public: std::string convertToString(double toConvert);
public: std::string convertToString(char toConvert);
public: int convertToInt(std::string toConvert);
public: std::string stringJoin(std::vector<int> toConvert, std::string separator);
public: std::string stringJoin(std::vector<std::string> toConvert, std::string separator);
public: std::vector<int> stringSplitToInt(std::string toConvert, std::string separator);
public: std::vector<std::string> stringSplitToString(std::string toConvert, std::string separator);
};
