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

#include "typedef.h"

class Term {
public:
    Term();
    
    virtual Point * operator()();
    
};

class ConstPoint : public Term {
public:
    Point * value;
    Const(Point * val);
    virtual Point * operator()();
    
};

class Var : public Term {
public:
    Var();
    virtual Point * operator()(Point * pt);
    
};

class North : public Term {
public:
    North();
    virtual Point * operator()(Point * pt);
};

class South : public Term {
public:
    South();
    virtual Point * operator()(Point * pt);
};

class East : public Term {
public:
    East();
    virtual Point * operator()(Point * pt);
};

class West : public Term {
public:
    West();
    virtual Point * operator()(Point * pt);
};

#endif /* TERM_H */

