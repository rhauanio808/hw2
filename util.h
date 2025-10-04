#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> intersectResult; // hold results

    //iterate through 1st set (s1)
    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) {
        // check if element in s1 is also in s2 
        if (s2.find(*it) != s2.end()) {
            intersectResult.insert(*it); // add to results
        }
    }
    return intersectResult;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

    std::set<T> unionResult = s2; // start with all elements in s2

    // iterate through 1st set (s1)
    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) {
        unionResult.insert(*it); // only add element if not already present
    }
    return unionResult;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
