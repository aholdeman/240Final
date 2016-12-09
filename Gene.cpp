/* 
 * File:   Gene.cpp
 * Author: Phoebe Ngo, Lauren Nix, Abby Holdeman
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
    leftArrayIndex = 0;
}

Gene::Gene(ifstream& infile) { //inputting Sequences
    length = rightArrayIndex = leftArrayIndex = 0;

    string Input = " ";
    char charInput[256] = " ";
    //finds how many sequences there are in file
    while (!infile.eof()) { //while the scanner is not at the end of the file
        getline(infile, Input); //skips the first line that will be an ID
        getline(infile, Input); //reads line and assigns it to the string Input
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
    while (length < counter) {
        getline(infile, Input);
        getline(infile, Input); // this is the actual sequence info
        int i = 0;
        while (Input[i] != '\0') { //checking for valid input
            if (Input[i] == 'C' || Input[i] == 'A' || Input[i] == 'G' || Input[i] == 'T') {
                charInput[i] = Input[i];
                i++;
            } else {
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
    Sequence target = sequenceArray[length - 1];
    searchRight(target, minOverlap); //searches right side of target against rest of sequences
    searchLeft(target, minOverlap); //searches left side of target against rest of sequences
}

void Gene::searchRight(Sequence target, int minOverlap) {

    
    cout << "searching right ... " << endl;
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        Sequence compare; //current index in SequenceArray
        bool YOTHEREISAMATCH = false;
        bool matchFound = false;
        int targetLength = target.length();
        //targetSubstr grabs last section of the root Sequence 
        Sequence targetSubstr = target.endSubstr((targetLength - minOverlap), targetLength);
        int i(0);
        while (i < length) { //checks each index for similarity to target
            compare = sequenceArray[i];
            int compareLength = compare.length();
            int j(0);
            while ((j + minOverlap) < compareLength) {
                //compareSubstr increments through current Sequence until finds overlap
                Sequence compareSubstr = compare.startSubstr(j, minOverlap + j);
                if (compareSubstr == targetSubstr) { //match is found
                    matchFound = true;
                    YOTHEREISAMATCH = true;
                    //sends current overlap found to keep track
                    minOverlap = findMaxOverlap(target, minOverlap, compare, j);
                    break;
                } else { //if substring in current sequence is not equal to target subsequence, move forward
                    j++;
                }
            }
            if (matchFound == true)
                break;
                i++; // if target subsequence not found in this sequence, moves on to next sequence
        }
        if (i >= length) { //if it's gotten through all the indexes and can't find a match, that will be the end of the completed sequence
            if (YOTHEREISAMATCH) {
                //current target Sequence is added to the right side without the overlap
                rightArray[rightArrayIndex++] = (target - targetSubstr);
                target = compare; //current index in SequenceArray is new target root
                searchRight(target, minOverlap); //recursive call with new target
            } else {
                rightArray[rightArrayIndex++] = (compare); //max overlap is found, send to rightArray to store
                isComplete = true; 
            }
        }
    }
}

//finds the maximum overlap between target and current Sequence index
int Gene::findMaxOverlap(Sequence target, int minSim, Sequence compare, int j) {
    //grabs end section of target Sequence for comparison
    Sequence targetSubstr = target.endSubstr((target.length() - minSim), target.length());
    //increments through current compare Sequence to find overlap
    Sequence compareSubstr = compare.startSubstr(j, minSim + j);
    if (compareSubstr == targetSubstr) { //overlap is found
        return findMaxOverlap(target, minSim++, compareSubstr, j++);
        //recursively calls with an increase to shift farther left into the compare Sequence
    } else {
        return minSim - 1; //if not a match anymore, needs to go back to last matched overlap (the max)
    }
}

void Gene::searchLeft(Sequence target, int minSim) {

    cout << "searching left nao" << endl;
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        Sequence compare;
        bool matchFound = false;
        bool YOTHEREISAMATCH = false;
        int targetLength = target.length();
        //grabs beginning of the target Sequence to create left side of completed Sequence
        Sequence targetSubstr = target.startSubstr(0, minSim);
        int i(0);
        while (i < length) { 
            //checks each index for similarity to target
            compare = sequenceArray[i];
            int compareLength = compare.length();
            int j(0);
            while ((j + minSim) < compareLength) {
                //increments through current compare Sequence until finds an overlap
                Sequence compareSubstr = compare.endSubstr((targetLength - minSim) - j, targetLength - j); //?
                if (compareSubstr == targetSubstr) {
                    matchFound = true;
                    YOTHEREISAMATCH = true;
                    //sends overlap to increment until the maximum overlap in current Sequence is found
                    minSim = findMaxOverlapLeft(target, minSim, compare, j);
                    cout << "going here " << endl;
                    break;
                } else {
                    j++; //keeps search going until finds the overlap
                }
            }
            if (matchFound == true) {
                cout << "to here" << endl;
                break;
            }
            i++;
        }
        if (i >= length) { //if it's gotten through all the indexes and can't find a match, that will be the end of the completed sequence
            if (YOTHEREISAMATCH) {
                cout << "HERE?" << endl;
                //adds current target to left side without the found overlap
                leftArray[leftArrayIndex++] = (target - targetSubstr);
                target = compare;
                searchLeft(target, minSim);
            } else {
                cout << "OR HERE" << endl;
                //if overlap not found, adds current compare Sequence to the left side
                leftArray[leftArrayIndex++] = (compare);
                isComplete = true;
            }
        }

    }

}

//takes overlap found in searchLeft and finds maximum overlap possible
int Gene::findMaxOverlapLeft(Sequence target, int minSim, Sequence compare, int j) {
    //increases range of overlap in target from left side
    Sequence targetSubstr = target.startSubstr(0, minSim + j);
    //increments through current compare Sequence to find overlap
    Sequence compareSubstr = compare.endSubstr((compare.length() - minSim) - j, compare.length() - j);
    if (compareSubstr == targetSubstr) {
        //continues searching with an increased minSim 
        return findMaxOverlapLeft(target, minSim++, compareSubstr, j++);
    } else {
        return minSim - 1; //max has been found
    }
}

void Gene::print(ofstream &ofs) {

    ofs << "Left Array: " << endl;
    int i = 0;
    while (i < length) { //prints to ouput file TEST with array
        ofs << leftArray[i];
        i++;
    }
    ofs << endl;
    ofs << "Right array:" << endl;
    int j = 0;
    while (j < length) { //prints to ouput file TEST with array
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