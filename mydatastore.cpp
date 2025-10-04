#include "mydatastore.h"
#include "util.h"
#include <iostream>

// constructor
MyDataStore::MyDataStore() {}

// destructor: cleanup dynamically allocated objects
MyDataStore::~MyDataStore() {
    
    // delete all products
    for(std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        delete *it;
    }
    // delete all users
    for(std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

// add a product to the data store
void MyDataStore::addProduct(Product* p) {
    products_.push_back(p);
}

// add a user to the data store
void MyDataStore::addUser(User* u) {
    std::string uname = convToLower(u->getName()); // store usernames in lowercase
    users_[uname] = u;
}

// Search for products given a list of search terms
    // type = 0 means AND search (all match)
    // type = 1 means OR search (any match)
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> results; // store results

    if(terms.empty()) return {}; // empty search

    // find matches for 1st search term
    for(std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        std::set<std::string> keys = (*it)->keywords();

        // if product keyword includes the 1st search term, add to results
        if(keys.find(convToLower(terms[0])) != keys.end()) {
            results.insert(*it);
        }
    }

    // process additional search terms
    for(size_t i = 1; i < terms.size(); i++) {
        std::set<Product*> matches; // temp set to store matches for current term

        // check product keywords matches seach term, add to temp set
        for(std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
            std::set<std::string> keys = (*it)->keywords();
            if(keys.find(convToLower(terms[i])) != keys.end()) {
                matches.insert(*it);
            }
        }
        // merge temp and results based on search type
        // AND search (intersection)
        if(type == 0) { 
            results = setIntersection(results, matches);
        } 
        // OR search (union)
        else {        
            results = setUnion(results, matches);
        }
    }

    return std::vector<Product*>(results.begin(), results.end());
}

// dump the product and user contents of the store in database format
void MyDataStore::dump(std::ostream& ofile) {
    // output product info
    ofile << "<products>" << std::endl;
    for(std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        (*it)->dump(ofile);   
    }
    ofile << "</products>" << std::endl;

    //oputput users info
    ofile << "<users>" << std::endl;
    for(std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);   
    }
    ofile << "</users>" << std::endl;
}

// add product to a user's cart
void MyDataStore::addToCart(const std::string& username, Product* p) {
    std::string uname = convToLower(username);

    // check if user exists
    if(users_.find(uname) == users_.end()) {
        std::cout << "Invalid request" << std::endl;
        return;
    }

    // otherwise add product
    carts_[uname].push_back(p);
}

// view a user's cart
void MyDataStore::viewCart(const std::string& username) {
    std::string uname = convToLower(username);
    
    // check if user exists
    if(users_.find(uname) == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    // check if cart is empty
    if(carts_[uname].empty()) {
        std::cout << "Cart empty" << std::endl;
        return;
    }
    // display items
    for(size_t i = 0; i < carts_[uname].size(); i++) {
        std::cout << "Item " << i+1 << ":" << std::endl; // item #
        std::cout << carts_[uname][i]->displayString() << std::endl;
    }
}

// buy items in the cart
void MyDataStore::buyCart(const std::string& username) {
    std::string uname = convToLower(username);
    
    // check if user exists
    if(users_.find(uname) == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    User* u = users_[uname];
    std::vector<Product*>& cart = carts_[uname];
    std::vector<Product*> unpurchased; // store items that cannot be bought

    for(size_t i = 0; i < cart.size(); i++) {
        Product* p = cart[i];
        if(p->getQty() > 0 && u->getTotal() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        } else {
            unpurchased.push_back(p); // keep item if not purchased
        }
    }
    cart = unpurchased; // update cart
}