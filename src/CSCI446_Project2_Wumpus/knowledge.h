/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   knowledge.h
 * Author: byrdie
 *
 * Created on October 15, 2016, 3:21 PM
 */

#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

// Define Predicates
#define P_NEGATION      0x80000000      // predicate inversion
#define P_BREEZY        0x00000001      // breezy predicate
#define P_PIT           0x00000002      // pit predicate
#define P_SAFE          0x00000004      // safe predicate

// Define Functions
#define F_IDENTITY      0x00010000      // Identity function returns itself
#define F_NORTH         0x00020000      // Returns the tile to the north
#define F_SOUTH         0x00040000      // Returns the tile to the south
#define F_EAST          0x00080000
#define F_WEST          0x00100000

#include <vector>

#include "rule_parser.h"

using namespace std;

typedef vector<int>             func_args;  // integer represents function parameters, variable index, or constant value
typedef tuple<int, func_args>   func;       // integer represents function name, variable type, or constant type
typedef vector<func>            pred_args;  // Arguments to predicates
typedef tuple<int, pred_args>   pred;       // Integer represents predicate name
typedef vector<vector<pred>>    cnf;        // CNF representation of all predicates

class Knowledge {
    
    cnf static_kb;
    
    Knowledge();
            
    
};

#endif /* KNOWLEDGE_H */

