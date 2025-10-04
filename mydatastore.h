#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <map>
#include <set>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    // functions from datastore
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    // extra menu commands
    void addToCart(const std::string& username, Product* p); // ADD
    void viewCart(const std::string& username); // VIEW
    void buyCart(const std::string& username); // BUY

private:
    // storage for products users, and cart
    std::vector<Product*> products_; // products
    std::map<std::string, User*> users_; // users
    std::map<std::string, std::vector<Product*> > carts_; // cart
    // std::map<std::string, std::set<Product*>> keywordIdx_;
};

#endif