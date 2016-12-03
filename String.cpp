/* 
 * File:   String.cpp
 * Author: PhoebeNgo
 * Function: Create custom String class
 * Input: char array
 * Output: String Object
 * 
 * Created on October 29, 2016, 6:47 PM
 */

#include "String.h"

//default
String::String() {
    _length = 0;
    data = new char[0];
}

//alternative constructor
String::String(char str[]) {
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
String::String(const String& orig) {
    _length = orig._length;
    data = new char[_length];
    
    for (int i=0; i<_length;i++) {
        data[i] = orig.data[i];
    }
}

//constructor that takes in char array and length of char array
String::String(char str[], const int length) {
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


//returns the length of the char[] inside the string class
int String::length() const{
    return _length;
}

////this method should clear the char[] within your String class.
void String::clear() {
    for(int i=0; i< _length; i++) {
         data[i] = 0;
    }
     _length = 0;
}

//this method should check to see if the char[] within the String class is empty or not.
bool String::empty() const {
    if(data == NULL || data[0] == 0) {
        return true;
    } else {
        return false;
    }
}

// this method should return the character at the position index. (deprecated by operator[])
char String::at(const int index) const {
    if (index < 0 || index > _length) {
        cout << "Invalid index" << endl;
        exit(0);
    }
    return data[index];
}

//this method should search for substring in the char[] within the calling String object starting from the startIndex.
int String::find(const char substr[], int startIndex) {
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

// this method should compare two String objects together and return true if they contain the same char[] or false if they do not. 
//(deprecated by the operator==
bool String::equal(const String &two) {
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

//this method will concatenate the char[] of String two to the char[] within the String calling the function. 
//Deprecated by the operator+. Note that for now, this method will always return the value of true. (deprecated by the operator+)
bool String::add(String &two) {
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
void String::print() const {
    if (empty()) {
        cout << "NULL";
    }
    for (int i=0;i<_length;i++) {
        cout << data[i];
    }
    cout << endl;
}

//replaces at() method
char & String::operator[](const int index) const {
    if (index < 0 || index >= _length) {
        cout << "Error: invalid index" << endl;
        exit(0);
    }
    return data[index];
}

//assigns the second operand to the calling object
String String::operator=(const String &two) {
    delete [] data;
    _length = two.length();
    data = new char[_length];
    for (int i=0;i<_length;i++) {
        data[i] = two[i];
    }
    return *this;
}

// replaces equal method
bool String::operator ==(const String &two) const {
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
String String::operator +(const String &two) {
    int newSize = _length + two._length;
    char temp[newSize]; //makes temporary char array to host concatenated strings
    
    for (int i=0;i<_length;i++) {
        temp[i] = data[i];
    }
    for (int i=0;i<two._length;i++) {
        temp[_length + i] = two[i];
    }

    //creates new String object
    String newString(temp, newSize);
    
    return newString;
    
}

//acts as the print function
ostream & operator <<(ostream &out, const String &two) {
    for (int i=0;i<two._length;i++) {
        cout << two[i];
    }
    
    return out;
}

//should take in a char[] and return its size by counting all the chars that occur before the terminal character.
int String::getCharArraySize(const char arr[]) { 
    int size(0);
    int i(0);

    while(arr[i] != '\0') {
        size++;
        i++;
    }
    return size;
}

//deletes data pointer
String::~String() {
    delete [] data;
}

