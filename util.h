#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	// blank new set for intersecting keywords
	std::set<T> intersection;

	for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it){
		// checking if s2 keyword exists in s1
		// only add s2's keyword if it DOES exist in s1
		if (s2.find(*it) != s2.end()){
			// find() returns <set>.end() if not found
			intersection.insert(*it);
		}
	}

	return intersection;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	// copy of s1
	std::set<T> uunion = s1;

	for (typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it){
		// checking if s2 keyword already exists in s1's copy
		// (by checking if in copy union)
		// only add s2's keyword if it DOES NOT, handles overlap
		if (uunion.find(*it) == uunion.end()){
			// find() returns <set>.end() if not found
			uunion.insert(*it);
		}
	}

	return uunion;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
