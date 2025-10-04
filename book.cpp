#include <sstream>
#include "book.h"
#include "util.h"

// book constructor
Book::Book(const std::string& name, double price, int qty,
           const std::string& isbn, const std::string& author)
    : Product("book", name, price, qty), isbn_(isbn), author_(author) {}

// returns set of keywords to be associated with book
std::set<std::string> Book::keywords() const {

    // book keywords: 
        // product name
        // author name
        // ISBN

    std::set<std::string> bookKeys = parseStringToWords(name_); // parse book name and add to book keys
    
    // parse aurthor name and add to book keys
    std::set<std::string> authorKeys = parseStringToWords(author_);  
    bookKeys.insert(authorKeys.begin(), authorKeys.end()); // add only unique genre keys to overall set

    bookKeys.insert(isbn_); // add isbn to book keys

    return bookKeys;
}

// returns a string to display the book info for hits of the search
std::string Book::displayString() const {
  // display: author, isbn, price, quantity

    return name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}


// outputs the book info in the database format
void Book::dump(std::ostream& os) const {
    Product::dump(os); // prints category, name, price, qty
    os << isbn_ << "\n" << author_ << std::endl;
 }