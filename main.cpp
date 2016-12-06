/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: abbyholdeman
 *
 * Created on December 5, 2016, 8:51 PM
 */

//THIS SHOULD GO IN GENE CLASS FILE
//main.cpp passes in char argv array with input file, output file, and min # overlap 
//split into four parts: 1) read in lines, make sequences
//2) form tree
//3) send node (root) with min # of overlapping characters to Sequence Class
//4) once finished, print tree to output file using in-order printing
//5) clear tree
// print execution time (in main.cpp)
#include <iostream>
#include <fstream>
#include "String.h"
using namespace std;


int main(int argc, char** argv) {
	//if the user does not input an input text file
	/* if (argc != 4) {
		cout << "Usage: " << argv[0] << "<inputfile.txt>" << "<outputfile.txt>" << "<size of overlap>"; //correct usage
		exit(1);
	}
         */
	ifstream ifs; //initializes the file reader

	ifs.open("testInput.txt"); //opens the specified file

	if(ifs.fail()){ //if there's an error
		cout << "Error opening the file" << argv[1] << "\n";
		exit(1);
	}

	string Input = " ";
        char charInput[256] = " ";

	int sequenceIndex = 0;

	while(!ifs.eof()) { //while the scanner is not at the end of the file
		getline(ifs, Input); //skips the first line that will be an ID
		getline (ifs, Input); //reads line and assigns it to the string Input
		sequenceIndex++;
	}
        int counter = sequenceIndex - 2;
        String *sequenceArray;
        sequenceArray = new String[sequenceIndex];
	

	sequenceIndex = 0;
	ifs.clear();
	ifs.seekg(0);
	while(sequenceIndex <= counter){
		getline(ifs, Input);
		getline (ifs, Input); // this is the actual sequence info
		int i = 0;
		while(Input[i] != '\0') {
			if(Input[i] == 'C' || Input[i] == 'A' || Input[i] == 'G' || Input[i] == 'T') {
				i++;
                                charInput[i] = Input[i];
			}
			else {
				cout << "Invalid input. Sequences must contain ONLY A, G, C, or T." << endl;
				exit(1);
			}
		}
        
                sequenceArray[sequenceIndex] = charInput;
		sequenceIndex++;
	}
	ifs.close(); //protect memory leaks
        //here we should call to form the tree
        //once tree is formed, call Sequence method compare and pass in size of comparision
        ofstream ofs; //initialize output stream
	ofs.open("testOutput.txt"); //open output file
	if(ofs.fail()){ //if there's an error
		cout << "There's an error." << endl;
		exit(1);
	}
	
	 int newSequenceIndex = 0; 
         while(newSequenceIndex <= counter) { //prints to ouput file TEST with array
             ofs << sequenceArray[newSequenceIndex] << endl;
             newSequenceIndex++;
	}
         
         ofs.close();

}