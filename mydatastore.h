#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <ostream>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore {
public:
		MyDataStore();
		~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    /**
     * Adding to cart helper
     */
    void addToCart(std::string username_in, Product* hit);

		/**
     * Buying cart helper
     */
    void buyCart(std::string username_in);

		// PUBLIC MASTER CART MAP DATA MEMBER
		// Maps user's name to their cart
    std::map<std::string, std::vector<Product*>> map_;

		// set of users
    std::set<User*> users_;


protected:


private:
    // DATA MEMBERS
    // set of all Products
    std::vector<Product*> products_;

		// map between each keyword (searchable terms)
		// and products that are associated with the keyword
		std::map<std::string, std::set<Product*>> search_terms_;

};

#endif
