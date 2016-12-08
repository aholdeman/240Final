/* 
 * File:   Sequence.cpp
 * Author: PhoebeNgo
 * Function: Create custom Sequence class
 * Input: char array
 * Output: Sequence Object
 * 
 * Created on October 29, 2016, 6:47 PM
 */

#include "Sequence.h"

//default
Sequence::Sequence() {
    _length = 0;
    data = new char[0];
}

//alternative constructor
Sequence::Sequence(char str[]) {
    _length = 0; 
    int i = 0;
    while(str[i] != '\0') { //finds length
        _length++;
        i++;
    }

    data = new char[_length];
    for (int i=0;i<_length;i++){ //assigns values of str[] to data pointer]
        data[i] = 0;
        data[i] = str[i];
    }
}

//copy constructor
Sequence::Sequence(const Sequence& orig) {
    _length = orig._length;
    data = new char[_length];
    
    for (int i=0; i<_length;i++) {
        data[i] = orig.data[i];
    }
}

//constructor that takes in char array and length of char array
Sequence::Sequence(char str[], const int length) {
    if (length < 0) {
        cout << "invalid length" << endl;
        exit(0);
    }
    _length = length;
    data = new char[_length];
    
    for(int i=0;i<_length;i++) {
        data[i] = str[i];
    }
}

String String::startSubstr(int begin, int end) {
    String subString;
    int indexSize = end-begin-1;
    char testSubstr[indexSize];
    int i(begin);
    while(i <= indexSize) {
        testSubstr[i] = data[i];
        i++;
    }
    subString = String(testSubstr, i);
    return subString;
}

String String::endSubstr(int begin, int end) {
    String subString;
    int indexSize = end-begin;
    char testSubstr[indexSize];
    int i(0);
    while(begin < end) {
        testSubstr[i] = data[begin];
        i++;
        begin++;
    }
    subString = String(testSubstr, i);
    return subString;
}

//returns the length of the char[] inside the string class
int Sequence::length() const{
    return _length;
}

////this method should clear the char[] within your Sequence class.
void Sequence::clear() {
    for(int i=0; i< _length; i++) {
         data[i] = 0;
    }
     _length = 0;
}

//this method should check to see if the char[] within the Sequence class is empty or not.
bool Sequence::empty() const {
    if(data == NULL || data[0] == 0) {
        return true;
    } else {
        return false;
    }
}

// this method should return the character at the position index. (deprecated by operator[])
char Sequence::at(const int index) const {
    if (index < 0 || index > _length) {
        cout << "Invalid index" << endl;
        exit(0);
    }
    return data[index];
}

//this method should search for substring in the char[] within the calling Sequence object starting from the startIndex.
int Sequence::find(const char substr[], int startIndex) {
    int position(-1);
    int strSize = getCharArraySize(data);
    int subStrSize = getCharArraySize(substr);
    
    for(int i=startIndex;i<strSize;i++) {
        if(data[i] == substr[0]) {
            position = i;
            for (int j=0;j<subStrSize;j++) {
                 if(data[position+j] != substr[j]) {
                     j = 1000;
                    position = -1;
                } else {
                    position = i;
                }
            }
            //if the program has already found the first instance of the substring, breaks
            if (position != -1) {
                i = 1000;
            }
        }
    }
    return position;
}

// this method should compare two Sequence objects together and return true if they contain the same char[] or false if they do not. 
//(deprecated by the operator==
bool Sequence::equal(const Sequence &two) {
     if (two.length() != _length) {
        return false;
    }
    for (int i=0;i<_length;i++) {
        if (data[i] != two[i]) {
            return false;
        }
    }
    return true;
}

//this method will concatenate the char[] of Sequence two to the char[] within the Sequence calling the function. 
//Deprecated by the operator+. Note that for now, this method will always return the value of true. (deprecated by the operator+)
bool Sequence::add(Sequence &two) {
    int length = _length + two.length();
    char temp[_length];
    
    for(int i=0;i<_length;i++) {
        temp[i] = data[i];
    }
    
    delete [] data; //get rid of old data
    data = new char[length]; //reallocate pointer to new array that can hold both
    
    for (int i=0;i<_length;i++) { //adds values from temp array back in to the pointer
        data[i] = temp[i];    
    }
    
    for (int j=0;j<two.length();j++) { //adds values from passed in object to the pointer
        data[_length + j] = two[j];
    }
    
    _length = length;
    return true;
}

//prints out value
void Sequence::print() const {
    if (empty()) {
        cout << "NULL";
    }
    for (int i=0;i<_length;i++) {
        cout << data[i];
    }
    cout << endl;
}

//replaces at() method
char & Sequence::operator[](const int index) const {
    if (index < 0 || index >= _length) {
        cout << "Error: invalid index" << endl;
        exit(0);
    }
    return data[index];
}

//assigns the second operand to the calling object
Sequence Sequence::operator=(const Sequence &two) {
    delete [] data;
    _length = two.length();
    data = new char[_length];
    for (int i=0;i<_length;i++) {
        data[i] = two[i];
    }
    return *this;
}

// replaces equal method
bool Sequence::operator ==(const Sequence &two) const {
     if (two.length() != _length) {
        return false;
    }
    for (int i=0;i<_length;i++) {
        if (data[i] != two[i]) {
            return false;
        }
    }
    return true;
}

//Should replace your add() method. Should append the char* in two to the object doing the calling. Return true if you were able to add the two together, false if not. 
Sequence Sequence::operator +(const Sequence &two) {
    int newSize = _length + two._length;
    char temp[newSize]; //makes temporary char array to host concatenated strings
    
    for (int i=0;i<_length;i++) {
        temp[i] = data[i];
    }
    for (int i=0;i<two._length;i++) {
        temp[_length + i] = two[i];
    }

    //creates new Sequence object
    Sequence newSequence(temp, newSize);
    
    return newSequence;
    
}

//acts as the print function
ostream & operator <<(ostream &out, const Sequence &two) {
    for (int i=0;i<two._length;i++) {
        cout << two[i];
    }
    
    return out;
}

//should take in a char[] and return its size by counting all the chars that occur before the terminal character.
int Sequence::getCharArraySize(const char arr[]) { 
    int size(0);
    int i(0);

    while(arr[i] != '\0') {
        size++;
        i++;
    }
    return size;
}

//deletes data pointer
Sequence::~Sequence() {
    delete [] data;
}

