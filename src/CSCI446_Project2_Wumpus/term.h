/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   term.h
 * Author: byrdie
 *
 * Created on October 15, 2016, 3:43 PM
 */

#ifndef TERM_H
#define TERM_H

#include <iostream>

#include "typedef.h"

using namespace std;

/* Class that serves as the basis of inputs to predicates */
class Term {
public:
    Term();     
};

/* Type of Term with an X and Y coordinate */
class Vec: public Term {
public:
    Point * pt;  
    Vec();
    virtual Point * operator()();    // General vec evaluation function
};

class Const : public Vec {
public:
    Const(Point * pt);
    virtual Point * operator()();
    
};

class Var : public Vec {
public:
    Var();
    virtual Point * operator()();
    
};

class North : public Vec {
public:
    Vec * inp;
    North(Vec * input);
    virtual Point * operator()();
};

class South : public Vec {
public:
    Vec * inp;
    South(Vec * input);
    virtual Point * operator()();
};

class East : public Vec {
public:
    Vec * inp;
    East(Vec * input);
    virtual Point * operator()();
};

class West : public Vec {
public:
    Vec * inp;
    West(Vec * input);
    virtual Point * operator()();
};

#endif /* TERM_H */

