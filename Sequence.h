/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sequence.h
 * Author: PhoebeNgo
 *
 * Created on December 2, 2016, 1:30 PM
 */

#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "String.h"

class Sequence : public String {
public:
    Sequence();
    Sequence(char str[]);
    Sequence(const Sequence& orig);
    virtual ~Sequence();
    setData(int index, char value);
    bool isChecked();
    Sequence compare(Sequence node);
    Sequence search(Sequence node);
private:

};

#endif /* SEQUENCE_H */

