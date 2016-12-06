/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
    length(0);
    sequenceArray = 0;
}

Gene::Gene(ifstream& infile) : length(0) {
    //finds how many sequences there are in file
    while(!infile.eof()) { //while the scanner is not at the end of the file
            getline(infile, "  "); //skips the first line that will be an ID
            getline (infile, "  "); //reads line and assigns it to the string Input
            length++;
    }
    
    sequenceArray = new Sequence[length];
    int i(0);
    while(!infile.eof()) {
        getline(infile, "  "); //skips the first line that will be an ID
        getline (infile, "  "); //reads line and assigns it to the string Input
        sequenceArray[i];
        i++;
    }
}

void Gene::insertRoot(Sequence seq) {
   //TODO 
}

void Gene::compare(Sequence &second) {
    //TODO
}

Gene::Gene(const Gene& orig) {
}

Gene::~Gene() {
    delete [] sequenceArray;
}

