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
    length = matchesArrayIndex = 0;    
    string inputLine = " ";
    //finds how many sequences there are in file
    while(!infile.eof()) { //while the scanner is not at the end of the file
            getline(infile, inputLine); //skips the first line that will be an ID
            getline (infile, inputLine); //reads line and assigns it to the string inputLine
            length++;
    }
    sequenceArray = new Sequence[length];
    matchesArray = new Sequence[length]; //will stay empty for now, eventually will fill up with values
    int counter = length - 2;
    char charinputLine[256] = " ";
   
    infile.clear();
    infile.seekg(0);
    int sequenceIndex = 0;
    while(sequenceIndex <= counter){
            getline(infile, inputLine); //skips sequence ID
            getline (infile, inputLine); // this is the actual sequence info
            int i = 0;
            while(inputLine[i] != '\0') {
                    if(inputLine[i] == 'C' || inputLine[i] == 'A' || inputLine[i] == 'G' || inputLine[i] == 'T') {
                            i++;
                            charinputLine[i] = inputLine[i];
                    }
                    else {
                            cout << "Invalid input. Sequences must contain ONLY A, G, C, or T." << endl;
                            exit(1);
                    }
            }
            sequenceArray[sequenceIndex] = charinputLine;
            sequenceIndex++;
    }
    
    //DELETEME
    int i(0);
    while(i <= length) {
        cout << sequenceArray[i] << endl;
        i++;
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
	 int newSequenceIndex = 0; 
         while(newSequenceIndex <= length) { //prints to ouput file TEST with array
             ofs << sequenceArray[newSequenceIndex] << endl;
             newSequenceIndex++;
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
