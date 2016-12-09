/* 
 * File:   Gene.cpp
 * Author: PhoebeNgo
 * 
 * Created on December 5, 2016, 9:21 PM
 */

#include "Gene.h"
#include "Sequence.h"
#include <iostream>

Gene::Gene() {
    length = 0;
    sequenceArray = 0;
}

Gene::Gene(ifstream& infile) {
    length = 0;    
    string Input = " ";
    char charInput[256] = " ";
    //finds how many sequences there are in file
    while(!infile.eof()) { //while the scanner is not at the end of the file
            getline(infile, Input); //skips the first line that will be an ID
            getline (infile, Input); //reads line and assigns it to the string Input
            length++;
    }
    
    infile.clear();
    infile.seekg(0);

    int counter = length - 1; //gets rid of blank space at the end of files
    sequenceArray = new Sequence[length];
    length = 0;
    infile.clear();
    infile.seekg(0);
    while(length < counter){
            getline(infile, Input);
            getline (infile, Input); // this is the actual sequence info
            int i = 0;
            while(Input[i] != '\0') {
                    if(Input[i] == 'C' || Input[i] == 'A' || Input[i] == 'G' || Input[i] == 'T') {    
                        charInput[i] = Input[i];
                        i++;
                    }
                    else {
                            cout << "Invalid input. Sequences must contain ONLY A, G, C, or T." << endl;
                            exit(1);
                    }
            }
            Sequence sequence = Sequence(charInput, i);
            sequenceArray[length] = sequence;
            length++;
    }
}

void Gene::search() {
    /*TODO 
     1. Go to last index, use last index sequence as target sequence
     2. Go to first index, cycle through until it finds a best match
     3. if best match is found, store the whole target sequence into new array
     3b. deletes the part that matches from target sequence
     4. move found match into the last index sequence's place
     5. */
    
    Sequence target = sequenceArray[length-1]; //last line is blank
    int minSim(20); //basis for minimum characters similar
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    
    while (!isComplete) {
        int targetLength = target.length(); 
        Sequence targetSubstr = target.endSubstr((targetLength - minSim), targetLength);
       
        int i(0);
        while(i < length){ //checks each index for similarity to target
            Sequence compare = sequenceArray[i]; //sequence it is currently looking at
            Sequence compareSubstr = compare.startSubstr(0, minSim);
            if(compareSubstr == targetSubstr) {
                cout << "Found a match at index " << i << endl; //not in final  code, just for now to make sure it's correct
               
                target -= targetSubstr; // gets rid of target substring from target
                
                target = compare; 
                break;
            }
            else {
                i++;
            }
        }
        //if it's gotten through all the indexes and can't find a match, that will be the end of the completed sequence
            isComplete = true;
    }
}

void Gene::compare(Sequence &second) {

}


void Gene::print(ofstream &outstream) {
	ofs.open("testOutput.txt"); //open output file
	if(ofs.fail()){ //if there's an error
		cout << "There's an error." << endl;
		exit(1);
	}
	int i = 0; 
   	 while(i < length) { //prints to ouput file TEST with array
        ofs << sequenceArray[i] << endl;
        i++;
   }
   ofs.close();
    }
}

Sequence Gene::at(int index) {
    return sequenceArray[index];
}

int Gene::getLength() {
    return length;
}

Gene::Gene(const Gene& orig) {
}

Gene::~Gene() {
    delete [] sequenceArray;
}
