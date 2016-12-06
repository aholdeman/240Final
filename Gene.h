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

using namespace std;

class Gene {
public:
    Gene();
    Gene(ifstream & infile);
    Gene(const Gene& orig);
    
    
    virtual ~Gene();
private:
    Sequence sequenceArray[];
    Sequence *data;
    int length;
};

#endif /* GENE_H */

