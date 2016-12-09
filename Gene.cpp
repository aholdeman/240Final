/* 
 * File:   Gene.cpp
 * Author: PhoebeNgo
 * 
 * Created on December 5, 2016, 9:21 PM
 */

#include "Gene.h"
#include "Sequence.h"

Gene::Gene() { //default constructor
    length = 0;
    sequenceArray = 0;
    rightArray = 0;
    rightArrayIndex = 0;
    leftArray = 0;
    leftArrayIndex=0;
}

Gene::Gene(ifstream& infile) { //inputing Sequences
    length = rightArrayIndex = leftArrayIndex = 0;    
   
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
    
    rightArray = new Sequence[length];
    leftArray = new Sequence[length];
    
    length = 0;
    infile.clear();
    infile.seekg(0);
    while(length < counter){
            getline(infile, Input); //skips ID
            getline (infile, Input); // this is the actual sequence info
            int i = 0;
            while(Input[i] != '\0') { //checking for valid input
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
            sequenceArray[length] = sequence; //puts input sequence into the array
            length++;
    }
}

void Gene::search(int minOverlap) {
    Sequence target = sequenceArray[length-1]; //starts search at end of gene
    searchRight(target, minOverlap); //searches right side of target against rest of sequences
    searchLeft(target,  minOverlap); //searches left side of target against rest of sequences
}

void Gene::searchRight(Sequence target, int minOverlap)    
{   
    Sequence originalTarget = target;
    
    Sequence compare;
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        bool matchFound = false; 
        //grabs last section of the root sequence
        Sequence targetSubstr = target.endSubstr((target.length() - minOverlap), target.length());
        int i(0);
        while (i < length) { //checks each index for similarity to target
            compare = sequenceArray[i];
            int j(0);
            while ((j + minOverlap) < compare.length()) {
                //increments throught current Sequence until finds overlap
                Sequence compareSubstr = compare.startSubstr(j, minOverlap+j);
                if (compareSubstr == targetSubstr) {
                    matchFound = true;
                    rightArray[rightArrayIndex++] = (target-targetSubstr);
                    //sends current overlap found to keep track
                    target = compare; 
                    break;
                } else { //if substring in currently looked at sequence is not equal to target subsequence, move foward
                    j++;
                }
            }
            if (matchFound == true) {
                break;
            }
            i++; // if target subsequence not found in this sequence, moves on to next sequence
        }
        if (i >= length) { //if it's gotten through all the indexes and can't find a match, that will be the end of the completed sequence
            if(matchFound == true){  
                //current target Sequence is added to right side without overlap
                rightArray[rightArrayIndex++] = (target-targetSubstr);
                target = compare; //current index in SequenceArray is new target root
                searchRight(target, minOverlap); //recursive call with new target
            }
            else {
                //max overlap is found, send to rightArray to store
                rightArray[rightArrayIndex++] = (target-targetSubstr); 
                isComplete = true;
            }
        }
    }
}

void Gene::searchLeft(Sequence target, int minSim) {
    Sequence compare;
   
    cout << "searching left ..." << endl;
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        bool matchFound = false;
        int targetLength = target.length();
        //grabs beginning of target Sequence to create left side of completed Sequence
        Sequence targetSubstr = target.startSubstr(0, minSim);
        targetSubstr.print();
        int i(0);
        while (i < length) { //checks each index for similarity to target
            Sequence compare = sequenceArray[i];
            compare.print();
            int compareLength = compare.length();
            int j(0);
            while ((j + minSim) < compareLength) {
                Sequence compareSubstr = compare.endSubstr((targetLength - minSim) - j, targetLength - j); //?
                if (compareSubstr == targetSubstr) {
                    matchFound = true;
                    leftArray[leftArrayIndex++] = (target-targetSubstr);
                    //sends overlap to increment until the maximum overlap in current Sequence is found
                    target = compare;
                    break;
                } else {
                    j++; //keeps search going until finds the overlap
                }
            }
            if (matchFound == true) {
    
                break;
            }
            i++;
        }
        if (i >= length) { //if it's gotten through all the indexes and can't find a match, that will be the end of the completed sequence
            if (matchFound == true) {
                cout << "leftArray:  " << endl; 
                leftArray[leftArrayIndex].print();
                target = compare;
                searchLeft(target, minSim);
            } else {
                //if overlap not found, adds target Sequence to left side
                leftArray[leftArrayIndex++] = (target);
                isComplete = true;
            }
        }
    }
}

void Gene::print(ofstream &ofs) {
    int i(length);
    while(i > 0) { //prints to output file TEST with array
        ofs << leftArray[i];
        i--;
   }
    cout << endl;
    int j(1); //skips over target Sequence 
    while(j < length) { //prints to output file 
        ofs << rightArray[j];
        j++;
    }
   ofs.close();

} 

int Gene::getLength() {
    return length;
}

Gene::Gene(const Gene& orig) {
}

Gene::~Gene() {
    delete [] sequenceArray;
}
