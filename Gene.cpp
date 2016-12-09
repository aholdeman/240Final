/* 
 * File:   Gene.cpp
 * Author: PhoebeNgo
 * 
 * Created on December 5, 2016, 9:21 PM
 */

#include "Gene.h"
#include "Sequence.h"

Gene::Gene() {
    length = 0;
    sequenceArray = 0;
    rightArray = 0;
    rightArrayIndex = 0;
    leftArray = 0;
    leftArrayIndex;
}

Gene::Gene(ifstream& infile) {
    length = rightArrayIndex = 0;    
    
    string Input = " ";
    char charInput[256] = " ";
    //finds how many sequences there are in file
    while(!infile.eof()) { //while the scanner is not at the end of the file
            getline(infile, Input); //skips the first line that will be an ID
            getline (infile, Input); //reads line and assigns it to the string Input
            length++;
    }
    leftArrayIndex = length; //sets left array index at the end and will decrement from there
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

void Gene::search(int minOverlap) {
    Sequence target = sequenceArray[length-1];
    searchRight(target, minOverlap);
    searchLeft(target,  minOverlap);
}

void Gene::searchRight(Sequence target, int minOverlap)    
{
    bool YOTHEREISAMATCH = false;
    bool matchFound = false;
    Sequence compare;
    cout << "searching right ... " << endl;
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        int targetLength = target.length();
        Sequence targetSubstr = target.endSubstr((targetLength - minOverlap), targetLength);
        int i(0);
        while (i < length) { //checks each index for similarity to target
            Sequence compare = sequenceArray[i];
            int compareLength = compare.length();
            int j(0);
            while ((j + minOverlap) < compareLength) {
                Sequence compareSubstr = compare.startSubstr(j, minOverlap+j);
                if (compareSubstr == targetSubstr) {
                    matchFound = true;
                    YOTHEREISAMATCH = true;
                    minOverlap = findMaxOverlap(target, minOverlap, compare, j);
                    target = compare; 
                } else { //if substring in currently looked at sequence is not equal to target subsequence, move foward
                    j++;
                }
            }
            if (matchFound == true)
                break;
            i++; // if target subsequence not found in this sequence, moves on to next sequence
        }
        if (i >= length) { //if it's gotten through all the indexes and can't find a match, that will be the end of the completed sequence
            if(YOTHEREISAMATCH){
             
            rightArray[rightArrayIndex++] = (target-targetSubstr);
            target = compare;
            searchRight(target, minOverlap);
            }
            else {
                rightArray[rightArrayIndex++] = (target-targetSubstr);
                isComplete = true;
            }
        }
    }
}

int Gene::findMaxOverlap(Sequence target, int minSim, Sequence compare, int j) {
    Sequence targetSubstr = target.endSubstr((target.length() - minSim), target.length());
    Sequence compareSubstr = compare.startSubstr(j, minSim+j);
    if(compareSubstr == targetSubstr) { 
        return findMaxOverlap(target, minSim++, compareSubstr, j++);
     } else {
        return minSim-1;
    }
}

void Gene::searchLeft(Sequence target, int minSim)
{
    bool matchFound = false;
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        int targetLength = target.length();
        Sequence targetSubstr = target.startSubstr(0, minSim);
        int i(0);
        while (i < length) { //checks each index for similarity to target
            Sequence compare = sequenceArray[i];
            int compareLength = compare.length();
            int j(0);
            while ((j + minSim) < compareLength) {
                Sequence compareSubstr = compare.endSubstr((targetLength - minSim)-j, targetLength-j); //?
                if (compareSubstr == targetSubstr) {
                    matchFound = true;
                    minSim = findMaxOverlap(target, minSim, compare, j);
                    target = compare; 
                
                bool noMatch = false;
                while(noMatch == false)
                {
                    //check for larger overlap
                    targetSubstr = target.startSubstr(0, minSim);
                    //this needs to change
                    compareSubstr = compare.endSubstr((targetLength - minSim)-j, targetLength-j);
                    if(compareSubstr == targetSubstr)
                    {
                        cout << "Found a BETTER match bc lorn ROX so here u go " << i << endl; 
                        minSim++;
                    }
                    else
                    {
                        //too far, overlap is over
                        noMatch = true;
                    }
                }
                searchLeft(target, minSim); 
                
                target = compare; 
                j++;
            }
                
            else {
                    j++;
            }
                i++;
        }
        if(i >= length) { //if it's gotten through all the indexes and can't find a match, that will be the end of the completed sequence
            isComplete = true;
           leftArray[leftArrayIndex--] = (target - targetSubstr);
        }
    }
   }                 
}

int Gene::findMaxOverlapLeft(Sequence target, int minSim, Sequence compare, int j) {
    Sequence targetSubstr = target.startSubstr(0, minSim);
    Sequence compareSubstr = compare.endSubstr((compare.length() - minSim)-j, compare.length()-j);
    if(compareSubstr == targetSubstr) { 
        return findMaxOverlapLeft(target, minSim++, compareSubstr, j++);
     } else {
        return minSim-1;
    }
}


void Gene::print(ofstream &ofs) {
    int i = 0; 
    while(i < length) { //prints to ouput file TEST with array
        ofs << sequenceArray[i] << endl;
        i++;
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
