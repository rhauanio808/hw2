#include <sstream>
#include "clothing.h"
#include "util.h"

// clothing constructor
Clothing::Clothing(const std::string& name, double price, int qty,
                   const std::string& size, const std::string& brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand) {}

// returns set of keywords to be associated with book
std::set<std::string> Clothing::keywords() const {
    
    // clothing keywords: 
        // product name
        // brand name
    
    std::set<std::string> clothingKeys = parseStringToWords(name_); // parse clothing name and add to clothing keys

    // set of keys to add clothing names 
    std::set<std::string> brandKeys = parseStringToWords(brand_);
    clothingKeys.insert(brandKeys.begin(), brandKeys.end()); // add only unique brand keys to overall set
    
    return clothingKeys;
}

// returns a string to display the book info for hits of the search
std::string Clothing::displayString() const {
    // display: name, size, brand, price, quantity
    return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

// outputs the clothing info in the database format
void Clothing::dump(std::ostream& os) const {
    Product::dump(os);  // product prints category, name, price, qty
    os << size_ << "\n" << brand_ << std::endl;
}