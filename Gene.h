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
    
    Tree();
    Tree(const Tree& orig);
    
    void insertRoot(Sequence seq); 
    void compare(Sequence &second);
    bool empty(); //checks if tree is empty through root
    
    virtual ~Gene();
    virtual ~Tree();
private:
    Sequence *sequenceArray;
    int length;
};

private:
    Sequence sequenceArray[];
    Sequence *data;
    int length;
    
    void clear(Node *leaf); //memory leaks
    void insertLeft(String value, Node *leaf);
    void insertRight(String value, Node *leaf);
    Node *search(String value, Node *leaf);
    Node *root; 
    void print(Node *root);
};


class Tree {
public:   
    void insert(String value); //not sure if need this one
   // Node *search(String value); //from Node class; //not sure if need this one
    
    bool empty(); //checks if tree is empty through root
    //bool delete(String value); //shouldn't need this one
private:
    void clear(Node *leaf); //memory leaks
    void insert(String value, Node *leaf);
    Node *search(String value, Node *leaf);
    Node *root; 
    void print(Node *root);
};

#endif /* GENE_H */

