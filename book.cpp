#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <set>
#include "product_parser.h"
#include "product.h"
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, 
				std::string isbn, std::string author)  
				:	Product(category, name, price, qty)
{
	isbn_ = isbn;
	author_ = author;
	
	// making keywords set of strings
	set<string> keywords_name = parseStringToWords(name_);
	set<string> keywords_author = parseStringToWords(author_);
	keywords_author.insert(isbn);

	keywords_ = setUnion(keywords_name, keywords_author);
}

Book::~Book()
{

}

/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Book::keywords() const
{
	return keywords_;
}

/**
* Allows for a more detailed search beyond simple keywords
*/
bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
	return false;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const
{
	return name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

