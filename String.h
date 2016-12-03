/* 
 * File:   String.h
 * Author: PhoebeNgo
 * Function: Create custom String class
 * Input: char array
 * Output: String Object
 *
 * Created on October 29, 2016, 6:47 PM
 */

#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstdlib>
using namespace std;

class String {
     friend ostream & operator<<(ostream &, const String &);
     
public:
    String();
    String(char str[]);
    String(const String& orig); //copy constructor
    String(char str[], const int length);
    
    int length() const;
    void clear();
    bool empty() const;
    char at(const int index) const; 
    int find(const char substr[], int startIndex);
    bool equal(const String &two);
    bool add(String &two); 
    void print() const; 
    
    char & operator[](const int index) const; 
    String operator=(const String& two); 
    bool operator==(const String& two) const;
    String operator+(const String& two); 
    virtual ~String();
    
private:
    int _length; //this should contain the actual size of the char[] housed within the object.
    char *data; // is the name of the pointer that points to the data structure which will hold the content of the string.
    int getCharArraySize(const char arr[]); //this function should take in a char[] and return its size by counting all the chars that occur before the terminal character.
};

#endif /* STRING_H */

