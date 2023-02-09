#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <set>
#include "product_parser.h"
#include "product.h"
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, 
				std::string size, std::string brand)  
				:	Product(category, name, price, qty)
{
	size_ = size;
	brand_ = brand;
	
	// making keywords set of strings
	std::set<std::string> keywords_name = parseStringToWords(name_);
	std::set<std::string> keywords_brand = parseStringToWords(brand_);

	keywords_ = setUnion(keywords_name, keywords_brand);
}

Clothing::~Clothing()
{

}

/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Clothing::keywords() const
{
	return keywords_;
}

/**
* Allows for a more detailed search beyond simple keywords
*/
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
	return false;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing::displayString() const
{
	return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

