/* 
 * File:   Sequence.h
 * Author: PhoebeNgo
 * Function: Create custom Sequence class
 * Input: char array
 * Output: Sequence Object
 *
 * Created on October 29, 2016, 6:47 PM
 */

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class Sequence {
     friend ofstream & operator<<(ofstream &, const Sequence &);
     
public:
    Sequence();
    Sequence(char str[]);
    Sequence(const Sequence& orig); //copy constructor
    Sequence(char str[], const int length);
    
    Sequence startSubstr(int begin, int end);
    Sequence endSubstr(int begin, int end);
    int length() const;
    void clear();
    bool empty() const;
    char at(const int index) const; 
    int find(const char substr[], int startIndex);
    bool equal(const Sequence &two);
    bool add(Sequence &two); 
    void print() const; 
    
    char & operator[](const int index) const; 
    Sequence operator=(const Sequence& two); 
    bool operator==(const Sequence& two) const;
    Sequence operator+(const Sequence& two); 
    Sequence operator-(const Sequence& two);
    virtual ~Sequence();
    
private:
    int _length; //this should contain the actual size of the char[] housed within the object.
    char *data; // is the name of the pointer that points to the data structure which will hold the content of the string.
    int getCharArraySize(const char arr[]); //this function should take in a char[] and return its size by counting all the chars that occur before the terminal character.
};

#endif /* SEQUENCE_H */