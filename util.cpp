#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    rawWords = convToLower(rawWords); // make all words lowercase
    trim(rawWords); // get rid of excess space on either side

    std::set<std::string> keywords; // store unique key words in set (no duplicates)
    string w;

    // iterate through string and store key words
    for (size_t i = 0; i < rawWords.size(); i++) {
        unsigned char c = static_cast<unsigned char>(rawWords[i]);
        
        // replace punctuation with space 
        if (i < rawWords.size()) {
            c = static_cast<unsigned char>(rawWords[i]);
        } 
        else {
            c = ' ';
        }

        // check if word is valid
        if (std::isalnum(c)) {
            w += c; // build a word until a space is reached
        } else {
            // only add words with 2 characters or more
            if (w.size() >= 2) {
                keywords.insert(w); // add valid word to key set
            }
            w = ""; // reset for next word
        }
    }
    // check last word
    if (w.size() >= 2) {
      keywords.insert(w); // add valid word to key set
    }

    return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
