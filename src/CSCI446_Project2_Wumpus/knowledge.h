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

// Define Functions

#define F_IDENTITY      0x00010000      // Identity function returns itself
#define F_NORTH         0x00020000      // Returns the tile to the north
#define F_SOUTH         0x00040000      // Returns the tile to the south
#define F_EAST          0x00080000
#define F_WEST          0x00100000

// Define Argument types
#define A_CONST     0x80000000      // predicate inversion
#define A_UNCONST   0x7FFFFFFF                   

#include <vector>
#include <iterator>                                                                                                                                                                                                                                                   



using namespace std;


typedef vector<uint> func_args; // integer represents function parameters, variable index, or constant value
typedef tuple<uint, func_args> func; // integer represents function name, variable type, or constant type
typedef vector<func> pred_args; // Arguments to predicates
typedef tuple<uint, pred_args> pred; // Integer represents predicate name
typedef vector<pred> clause; // Clauses are ORs of predicates
typedef vector<clause> cnf; // CNF representation of all clauses

class Knowledge;

#include "rule_parser.h"

class Knowledge {
public:
    RuleParser * rule_parser;
    cnf static_kb;
    cnf dynamic_kb;
    cnf total_kb;

    Knowledge();

    vector<uint> unification(pred x, pred y, vector<vector<uint>. theta);
    bool resolution(cnf kb, clause query);
    cnf resolve(clause c_i, clause c_j);

    bool is_neg(pred p);

    clause apply_sub_to_clause(clause c, vector<uint> sub);
    pred apply_sub_to_pred(pred p, vector<uint> sub);
    pred_args apply_sub_to_pred_args(pred_args pa, vector<uint> sub);
    func apply_sub_to_func(func f, vector<uint> sub);
    func_args apply_sub_to_func_args(func_args fa, vector<uint> sub);

    cnf concat_kb(cnf c1, cnf c2);

    cnf copy_kb(cnf kb);
    clause copy_clause(clause c);
    pred copy_pred(pred p);
    pred_args copy_pred_args(pred_args pa);
    func copy_func(func f);
    func_args copy_func_args(func_args fa);

    void del_kb(cnf kb);
    void del_clause(clause c);
    void del_pred(pred p);
    void del_pred_args(pred_args pa);
    void del_func(func f);
    void del_func_args(func_args fa);

    void print_kb(cnf kb);
    void print_clause(clause c);
    void print_pred(pred p);
    void print_pred_args(pred_args pa);
    void print_func(func f);
    void print_func_args(func_args fa);

#include "inference.h"

};


#endif /* KNOWLEDGE_H */

