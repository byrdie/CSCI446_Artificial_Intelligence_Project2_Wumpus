/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   predicate.h
 * Author: byrdie
 *
 * Created on October 15, 2016, 3:24 PM
 */

#ifndef PREDICATE_H
#define PREDICATE_H

#include <iostream>

#include "typedef.h"
#include "term.h"

using namespace std;

class Predicate {
public:
    bool negation;
    virtual bool operator()();
    Predicate(bool neg);
    
};

class Breezy : public Predicate {
public:
    
    Term * arg1;
    
    virtual bool operator()();
    
    Breezy(bool neg, Term * inp1);
    
};

#endif /* PREDICATE_H */

