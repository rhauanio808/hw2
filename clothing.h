#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"

class Clothing : public Product {
public:
    // constructor
    Clothing(const std::string& name, double price, int qty,
             const std::string& size, const std::string& brand);

    // key functions from Product
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    // clothing specific members
    std::string size_;
    std::string brand_;
};

#endif