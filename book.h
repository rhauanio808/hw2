#ifndef BOOK_H
#define BOOK_H

#include "product.h"

class Book : public Product {
public:
    // constructor
    Book(const std::string& name, double price, int qty,
         const std::string& isbn, const std::string& author);

    // functions from Product 
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    // book specific members
    std::string isbn_;
    std::string author_;
};

#endif