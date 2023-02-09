#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "user.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;


    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if ( cmd == "ADD") {
							string username_in;
							int hit_result_index;

                if (ss >> username_in >> hit_result_index){
                    // checking for invalid read-in's
                    if (hit_result_index - 1 >= (int) hits.size() || (hit_result_index - 1) < 0){
                        cout << "Invalid request" << endl;
                    }
                    else {
											// add helper function checks username for validity
                      ds.addToCart(username_in, hits[hit_result_index - 1]);
                    }
                }
                else{
                    cout << "Invalid request" << endl;
                }
            }
            else if ( cmd == "VIEWCART") {
            	// reading in username
              string username_in;
              if (ss >> username_in){
                map<string, vector<Product*>>::iterator it = ds.map_.begin();
                it = ds.map_.find(username_in);

                // if username not provided or invalid, print "Invalid username"
                if (it == ds.map_.end()){
                  cout << "Invalid username" << endl;
                }
                else{
                  // find username's cart in MyDataStore map
                  vector<Product*> curr_cart = it->second;

                  // for each item in cart:
                  for (size_t i = 0; i < curr_cart.size(); i++){
                    // print index number - item name
                    cout << "Item " << i+1 << endl;
                    cout << curr_cart[i]->displayString() << endl;
                  }
                }
							}
              else {
                cout << "Invalid username" << endl;
              }
              
            }
            else if ( cmd == "BUYCART") {
							// "Note: Your cart implementation must iterate through 
							// the products in the order they were added."
              // reading in username
              string username_in;
              if (ss >> username_in){
								// helper function checks internally if username is valid
								ds.buyCart(username_in);
							}
							else {
								cout << "Invalid username" << endl;
							}
            }
            else {
              cout << "Unknown command" << endl;
            }
        }
		}
    return 0;
}

// ASK: QUITTING PART 5 STEP 6???


void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
