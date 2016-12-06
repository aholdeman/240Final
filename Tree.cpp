/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.cpp
 * Author: laurennix
 * 
 * Created on December 4, 2016, 6:53 PM
 */

#include "Tree.h"

struct Node //structure class for node
{
    String key_value;
    struct Node *left;
    struct Node *right;
    
    Node()
    {
        left='/n'; //fix this to null
        right='/n'; //fix this to null
    }
};

Tree::Tree() {
    root = '/n'; //fix this to null
}

Tree::Tree(const Tree& orig) {
}

//destructor
Tree::~Tree() {
    clear(); //calls deleting method
}

void Tree:: clear(Node *leaf)
{
    if(leaf != '/n') //fix this to null
    {
        clear(leaf->left); //clears left tree
        clear(leaf->right); //clears right tree
        delete leaf; //deletes allocated memory 
    }
}

bool Tree:: empty()
{
    return(root == '/n'); //fix this to null
}


////public search method- user just needs value to search for, not root
//Node Tree:: *search(String value)
//{
//    return search(value, root); //calls actual search method
//}

Node Tree:: *search(String value, Node *leaf)
{
    if(leaf!= '/n') //fix this
    {
        if(value==leaf-> key_value) //found 
        {
            return leaf;
        }
        if(value < leaf -> key_value) //need to search left side
        {
            return search(value, leaf -> left);
        }
        else //need to search right side
        {
            return search(value, leaf -> right); 
        }
    }
    else
    {
        return '/n'; //fix this to null
    }
}

//insert function for if root isn't initialized yet
void Tree:: insert(String value) 
{
    if(root != '/n') //call other insert method - fix to null
    {
        insert(value, root);
    }
    else //root isn't initialized 
    {
        Node *newNode; //create new Node class node in tree
        root = newNode; 
        root -> key_value = value; //sets all equal
        root -> left = '/n'; //establishing tree // fix to null
        root -> right = '/n'; //establishing tree // fix to null
    }
}

void Tree:: insert(String value, Node *leaf)
{
    if(value < leaf -> key_value) //goes to left tree
    {
        if(leaf -> left != '/n') //fix to null
        {
        insert(value, leaf -> left); //recursive call
        }
        else
        {
            Node *newNode; //creating new node in tree
            newNode = new Node(); //need this?
            leaf -> left=newNode; //points to left of current node 
            newNode -> key_value = value; //sets equal to sequence value
            newNode -> left = '/n'; //sets new node's left child to null
            newNode -> right = '/n'; //sets new node's right child to null
        }
    } 
    else if(value >= leaf -> key_value)
    {
        if(leaf -> right!= '/n') //fix to null
        {
            insert(value, leaf -> right); //recursive call
        }
        else
        {
            Node *newNode; //creating new node in tree
            newNode = new Node();
            leaf -> right = newNode; //points to right of current node
            newNode -> key_value = value; //sets equal to sequence value
            newNode -> left = '/n'; //sets new node's left child to null
            newNode -> right = '/n'; //sets new node's right child to null
        }
    }
}

void print(Node *root) //in order traverse print
{
    //need to go all the way to the left most child in tree, print
    //then print that node's root, etc until reach root of tree
    //then print root's right child, and that node's right child, etc
    //until reach the right most node
    
    if(root != '/n') //fix to null
    {
        print(root -> left); 
        //need to print root
        print(root -> right);
    }
}


