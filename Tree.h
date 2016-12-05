/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.h
 * Author: laurennix
 *
 * Created on December 4, 2016, 6:53 PM
 */

#ifndef TREE_H
#define TREE_H



class Tree {
public:
    Tree();
    Tree(const Tree& orig);
    virtual ~Tree();
    
    void insert(String value); //not sure if need this one
    Node *search(String value); //from Node class; //not sure if need this one
    
    bool empty(); //checks if tree is empty through root
    //bool delete(String value); //shouldn't need this one
private:
    void clear(Node *leaf); //memory leaks
    void insert(String value, Node *leaf);
    Node *search(String value, Node *leaf);
    Node *root; 
    void print(Node *root);

    
};

#endif /* TREE_H */

