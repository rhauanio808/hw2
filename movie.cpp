#include <sstream>
#include "movie.h"
#include "util.h"

// movie constructor
Movie::Movie(const std::string& name, double price, int qty,
             const std::string& genre, const std::string& rating)
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

// returns set of keywords to be associated with movie
std::set<std::string> Movie::keywords() const {
    
    // movie keywords: 
        // product name
        // genre

    std::set<std::string> movieKeys = parseStringToWords(name_); //  add name to key words
    // parse movie genre and add to key words
    std::set<std::string> genreKeys = parseStringToWords(genre_); 
    movieKeys.insert(genreKeys.begin(), genreKeys.end()); // add only unique genre keys to overall set

    return movieKeys;
}

// returns a string to display the movie info 
std::string Movie::displayString() const {
  // display: genre, rating, price, quantity

    return name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

// outputs the movie info in the database format
void Movie::dump(std::ostream& os) const {
    Product::dump(os);  // prints category, name, price, qty
    os << genre_ << "\n" << rating_ << std::endl;
}