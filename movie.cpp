#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <set>
#include "product_parser.h"
#include "product.h"
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, 
				std::string genre, std::string rating)  
				:	Product(category, name, price, qty)
{
	genre_ = genre;
	rating_ = rating;
	
	// making keywords set of strings
	std::set<std::string> keywords_name = parseStringToWords(name_);
	std::set<std::string> keywords_genre = parseStringToWords(genre_);

	keywords_ = setUnion(keywords_name, keywords_genre);
}

Movie::~Movie()
{

}

/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Movie::keywords() const
{
	return keywords_;
}

/**
* Allows for a more detailed search beyond simple keywords
*/
bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
	return false;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const
{
	return name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

