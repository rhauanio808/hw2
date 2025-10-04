#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

class Movie : public Product {
public:
    // constructor
    Movie(const std::string& name, double price, int qty,
          const std::string& genre, const std::string& rating);

    // key functions from product
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    // movie specific members
    std::string genre_;
    std::string rating_;
};

#endif