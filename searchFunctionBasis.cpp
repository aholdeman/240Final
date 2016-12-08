/*
 * Hey friends this is the code for the search/compare function
 * It's not complete, but it finds all the matches until it finds the end of the completed sequence
 * still to be do with this:
 *                          - find all the matches before the last sequence in the original sequence array
 *                          - put matches in two arrays, either before the original sequence target or after
 *                                               (also, delete the overlapping characters)
 *                          - increment the overlapping characters each check to make sure it's the most similar sequence
 *                          - HAVE FUN :) ;)
 * 
 * 
 * Love always and forever,
 * 
 * Abby <3
 * 
 
 
 
 */

#include <iostream>
#include <fstream>
#include "String.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ifstream infile; //initializes the file reader

    infile.open("10000input"); //opens the specified file

    if (infile.fail()) { //if there's an error
        cout << "Error opening the file" << argv[1] << "\n";
        exit(1);
    }

    int length = 0;
    string Input = " ";
    char charInput[256] = " ";
    //finds how many sequences there are in file
    while (!infile.eof()) { //while the scanner is not at the end of the file
        getline(infile, Input); //skips the first line that will be an ID
        getline(infile, Input); //reads line and assigns it to the string Input
        length++;
    }
    int newArrayIndex = length-1;
    String *sequenceArray;
    sequenceArray = new String[length];


    length = 0;

    infile.clear();
    infile.seekg(0);
    while (length < newArrayIndex) {
        getline(infile, Input);
        getline(infile, Input); // this is the actual sequence info
        int i = 0;
        while (Input[i] != '\0') {
            if (Input[i] == 'C' || Input[i] == 'A' || Input[i] == 'G' || Input[i] == 'T') {
                charInput[i] = Input[i];
                i++;
            } else {
                cout << "Invalid input. Sequences must contain ONLY A, G, C, or T." << endl;
                exit(1);
            }
        }
        String sequence = String(charInput, i);
        sequenceArray[length] = charInput;
        length++;
    }
    
    
    String target = sequenceArray[length-1]; //last line is blank
    int minSim(20); //basis for minimum characters similar
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        int targetLength = target.length(); 
        String targetSubstr = target.endSubstr((targetLength - minSim), targetLength);
       
        int i(0);
        while(i < length){ //checks each index for similarity to target
            String compare = sequenceArray[i];
            String compareSubstr = compare.startSubstr(0, minSim);
            if(compareSubstr == targetSubstr) {
                cout << "Found a match at index " << i << endl; //not in final  code, just for now to make sure it's correct
                target = compare; 
                break;
            }
            else {
                i++;
            }
        }
        if(i >= length) { //if it's gotten through all the indexes and can't find a match, that will be the end of the completed sequence
            isComplete = true;
        }
    }
    

    return 0;
}

