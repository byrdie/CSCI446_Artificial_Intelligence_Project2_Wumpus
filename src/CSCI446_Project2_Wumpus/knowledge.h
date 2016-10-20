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
#define P_UNNEGATION    0x7FFFFFFF
#define P_BREEZY        0x00000001      // breezy predicate
#define P_PIT           0x00000002      // pit predicate
#define P_SAFE          0x00000004      // safe predicate
#define P_WALL          0x00000008
// Define Functions
// These must be larger than variables!
// Should all functions be invertible?
#define F_CONST         0x00008000      // Constant function
#define F_VAR           0x00010000      // Variable function
#define F_NORTH         0x00020000      // Returns the tile to the north
#define F_SOUTH         0x00040000      // Returns the tile to the south
#define F_EAST          0x00080000
#define F_WEST          0x00100000

// Define Argument types
#define A_CONST     0x80000000      // predicate inversion
#define A_UNCONST   0x7FFFFFFF                   

#include <iostream>
#include <vector>
#include <iterator>       
#include <functional>



using namespace std;


typedef vector<uint> func_args; // integer represents function parameters, variable index, or constant value
typedef tuple<uint, func_args> func; // integer represents function name, variable type, or constant type
typedef vector<func> pred_args; // Arguments to predicates
typedef tuple<uint, pred_args> pred; // Integer represents predicate name
typedef vector<pred> clause; // Clauses are ORs of predicates
typedef vector<clause> cnf; // CNF representation of all clauses

typedef vector<vector<func>> theta;     // A list of substitutions

class Knowledge;

#include "rule_parser.h"

class Knowledge {
public:
    
    RuleParser * rule_parser;
    cnf static_kb;
    cnf dynamic_kb;
    cnf total_kb;
    
    map<int, int> func_inv;

    Knowledge(string filename);

    theta unification(pred x, pred y, theta sub_list);  
    theta unify_func(func x, func y, theta sub_list);
    theta unify_var(func x, func y, theta sub_list);
    vector<vector<uint>> unify_arg(uint x, uint y, vector<vector<uint>> sub_list);
    theta sub_var(func x, func y, theta sub_list);      // x is assumed to be a variable
            
    bool resolution(cnf kb, clause query);
    cnf resolve(clause c_i, clause c_j);

    bool is_neg(pred p);
    cnf negate_clause(clause c);

    clause apply_sub_to_clause(clause c, vector<func> sub);
    pred apply_sub_to_pred(pred p, vector<func> sub);
    pred_args apply_sub_to_pred_args(pred_args pa, vector<func> sub);
    func apply_sub_to_func(func f, vector<func> sub);
    
    bool clause_eq(clause f, clause g);
    bool pred_eq(pred f, pred g);
    bool pred_args_eq(pred_args f, pred_args g);
    bool func_eq(func f, func g);
    bool func_args_eq(func f, func g);

    cnf concat_cnf(cnf c1, cnf c2);
    cnf add_clause(cnf kb, clause c);
    clause concat_clause(clause c1, clause c2);
    cnf union_cnf(cnf c1, cnf c2);
    bool subset(cnf c1, cnf c2);
    void print_kb(cnf kb);
    void print_clause(clause c);
    void print_pred(pred p);
    void print_pred_args(pred_args pa);
    void print_func(func f);
    void print_func_args(func_args fa);
    
    func build_func(uint function, func_args args);
    func build_fvar(uint arg);
    pred build_pred(uint predicate, pred_args args);
};


#endif /* KNOWLEDGE_H */

