#include <vector>
#include <set>
#include <map>
#include <string>
#include <ostream>
#include <algorithm>
#include "mydatastore.h"
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
using namespace std;

// Inhereted class should:
// make set of users (string or user object), products
// make a map of <users/string_username, carts>
// each cart is a vector of products


MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
	for (size_t i = 0; i < products_.size(); i++){
		delete products_[i];
	}
	
	for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
		delete *it;
	}

}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p)
{
	// to products set
	products_.push_back(p);
	set<string> temp_keywords = p->keywords();

	// to keyword set
	// for each keyword of Product p
	for (std::set<std::string>::iterator it = temp_keywords.begin(); it != temp_keywords.end(); ++it){
		// if the keyword is already in search_terms_,
		// add Product p to key's corresponding vector
		if (search_terms_.find(*it) != search_terms_.end()){
			search_terms_.find(*it)->second.insert(p);
		}
		// add keyword as a key in search_terms_
		// add Product p to its key
		else{
			std::set<Product*> temp;
			temp.insert(p);
			search_terms_.insert(std::pair<std::string, set<Product*>>(*it, temp));
		}
	}

}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u)
{
	// add u's username to map_ here
	map_.insert(std::pair<std::string, vector<Product*>>(u->getName(), NULL));
	// to users set
	users_.insert(u);
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	set<Product*> search_results_set;
	if (terms.size() > 0){
		search_results_set = search_terms_[terms[0]];
	}

	// looking through each term
	for (size_t i = 0; i < terms.size(); i++){
		// when a term matches a keyword
		if (search_terms_.find(terms[i]) != search_terms_.end()){
			if (type == 0){ // AND
				search_results_set = setIntersection(search_results_set, search_terms_.find(terms[i])->second);
			}
			else if (type == 1){ // OR
				search_results_set = setUnion(search_results_set, search_terms_.find(terms[i])->second);
			}
		}
	}

	// convert search_results set into a vector
	vector<Product*> search_results_vector;
	for (std::set<Product*>::iterator it = search_results_set.begin(); it != search_results_set.end(); ++it){
		search_results_vector.push_back(*it);
	}

	return search_results_vector;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << endl;
	for (std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
		// prints dump of all products
		(*it)->dump(ofile);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for (std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
		// prints dump of all users
		(*it)->dump(ofile);
	}
	ofile << "</users>" << endl;
}

void MyDataStore::addToCart(std::string username_in, Product* hit){
	// checking if username is valid
	bool username_is_valid = false;
	for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
		if ((*it)->getName() == username_in){
			username_is_valid = true;
		}
	}
	if (username_is_valid){
		map<string, vector<Product*>>::iterator it = map_.begin();
		it = map_.find(username_in);
		if (it == map_.end()){
			vector<Product*> newcart;
			newcart.push_back(hit);
			map_.insert(pair<string, vector<Product*>>(username_in, newcart));
		}
		else{
			it->second.push_back(hit);
		}
	}
	else{
    cout << "Invalid request" << endl;
  }

}

void MyDataStore::buyCart(std::string username_in){
	// checking if username is valid
	map<string, vector<Product*>>::iterator it = map_.begin();
	it = map_.find(username_in);

	if (it != map_.end()){
		// find username's cart in MyDataStore map
		User* curr_user;
		double budget;

		// find username's object pointer in users_
		for (set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
			if ((*it)->getName() == username_in){
				curr_user = (*it);
			}
		}

		unsigned int i = 0;
		
		while (i < it->second.size()){
			budget = curr_user->getBalance();
			Product* curr_prod = it->second[i];
			if (budget >= curr_prod->getPrice() && curr_prod->getQty() > 0){
				curr_prod->subtractQty(1);
				curr_user->deductAmount(curr_prod->getPrice());

				it->second.erase(it->second.begin() + i, it->second.begin() + i + 1);
			}
			else{
				i++;
			}
		}
	}
	else{
		cout << "Invalid username" << endl;
	}

}
