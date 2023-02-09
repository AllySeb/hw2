#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	// set of key words act as data member for each product type
	// in their product specific constructor classes
	std::set<std::string> keywords;
	rawWords = convToLower(rawWords);

	std::string temp = "";

	for (size_t i = 0; i < rawWords.size(); i++){
		// iterates until no longer a letter or number
		if ((rawWords[i] >= '0' && rawWords[i] <= '9') 
			|| (rawWords[i] >= 'a' && rawWords[i] <= 'z')){
			temp += rawWords[i];
		}

		else if (temp.length() > 1){
			// runs once it hits a non-alpha or non-num char
			// meets substring requirements
			keywords.insert(temp);

			// clearing temp
			temp = "";
		}
		else{
			// clearing temp
			temp = "";
		}
	}

	// handles last keyword occurence
	if (temp.length() > 1){
		keywords.insert(temp);
	}

	return keywords;
}


/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
