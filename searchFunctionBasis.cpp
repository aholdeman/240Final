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
#include "Sequence.h"

using namespace std;

/*
 * 
 */



Sequence searchRight(Sequence target, int minSim, int length, Sequence *sequenceArray)    
{
    
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        int targetLength = target.length(); 
        Sequence targetSubstr = target.endSubstr((targetLength - minSim), targetLength);
       
        int i(0);
        while(i < length){ //checks each index for similarity to target
            Sequence compare = sequenceArray[i];
            Sequence compareSubstr = compare.startSubstr(0, minSim);
            if(compareSubstr == targetSubstr) {
                cout << "Found a match at index " << i << endl; //not in final  code, just for now to make sure it's correct
                cout << "lets find a better match lolz" << endl;
                //need to keep searching for better match
                //add 1 to the minSim, which adds 1 to targetSubstr
                //how to just search the found compare string?
                minSim++; 
                
                bool noMatch = false;
                while(noMatch == false)
                {
                    //check for larger overlap
                    targetSubstr = target.endSubstr((targetLength - minSim), targetLength);
                    compareSubstr = compare.startSubstr(0, minSim);
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
                
                return searchRight(target, minSim, length, sequenceArray); 
                
                
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
}

Sequence searchLeft(Sequence target, int minSim, int length, Sequence *sequenceArray)
{
    bool isComplete = false; //has it finished checking all of the indexes for available matches?
    while (!isComplete) {
        int targetLength = target.length(); 
        Sequence targetSubstr = target.startSubstr((0), minSim); //left section of the target to check for
       
        int i(0);
        while(i < length){ //checks each index for similarity to target
            Sequence compare = sequenceArray[i];
            Sequence compareSubstr = compare.endSubstr((targetLength - minSim), targetLength);
            if(compareSubstr == targetSubstr) {
                cout << "Found a match at index " << i << endl; //not in final  code, just for now to make sure it's correct
                cout << "lets find a better match lolz" << endl;
                //need to keep searching for better match
                //add 1 to the minSim, which adds 1 to targetSubstr
                //how to just search the found compare string?
                minSim++; 
                
                bool noMatch = false;
                while(noMatch == false)
                {
                    //check for larger overlap
                    targetSubstr = target.startSubstr(0, minSim);
                    compareSubstr = compare.endSubstr((targetLength - minSim), targetLength);
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
                
                return searchLeft(target, minSim, length, sequenceArray); 
                
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
}
    
 int main(int argc, char** argv) {
    ifstream infile; //initializes the file reader

    infile.open("poop"); //opens the specified file

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
    Sequence *sequenceArray;
    sequenceArray = new Sequence[length];


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
        Sequence sequence = Sequence(charInput, i);
        sequenceArray[length] = charInput;
        length++;
    }
    Sequence target = sequenceArray[length-1]; //last line is blank
    int minSim(2); //basis for minimum characters similar
       return 0;
    //calling search functions
    searchRight(target, minSim, length, sequenceArray); 
    searchLeft(target, minSim, length, sequenceArray);
    
}




