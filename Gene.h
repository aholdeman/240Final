/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gene.h
 * Author: PhoebeNgo
 *
 * Created on December 5, 2016, 9:21 PM
 */


#ifndef GENE_H
#define GENE_H
#include <fstream>
#include "Sequence.h"
#include <iostream>

using namespace std;

class Gene {
public:
    Gene();
    Gene(ifstream & infile);
    Gene(const Gene& orig);
    
    void search();
    void compare(Sequence &second);
    bool empty(); //checks if tree is empty through root
    int getLength();
    Sequence at(int index);
    
    virtual ~Gene();
private:
    Sequence *sequenceArray;
    Sequence *matchesArray;
    int matchesArrayIndex;
    int length;
};

#endif /* GENE_H */