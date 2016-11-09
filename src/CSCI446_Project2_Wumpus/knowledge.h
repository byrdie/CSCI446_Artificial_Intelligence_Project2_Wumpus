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

#define debug_mode true

#include <iostream>
#include <vector>
#include <iterator>       
#include <functional>

using namespace std;

class Knowledge;

#include "typedef.h"
#include "rule_parser.h"

/* This class forms a theorem prover, optimized for the wumpus world */
class Knowledge {
public:

    uint N; // The size of the cave
    RuleParser * rule_parser;

    /* Static rules, loaded from file */
    cnf kb_rules; // Rules containing variables

    /* Dynamic rules, filled by the agent */
    cnf2D * kb_world_heap; // Rules are stored by position
    cnf kb_time_stack; // Rules are added on the back. these rules contain time

    ofstream out;
    ofstream latex;


    map<int, int> func_inv;

    Knowledge(uint sz, vector<string> rule_files);

    void clear_heap(uint x, uint y);
    void clear_stack();
    void add_to_rules(pred_name pname, func_arg parg);
    void add_percept_to_heap(pred_name pname, func_arg parg, uint x, uint y);
    void add_percept_to_heap(pred_name pname, pred_arg parg, uint x, uint y);
    void heap_to_stack(vector<Point *> pts);
    void add_percept_to_stack(pred_name pname, func_arg parg);

    /* Set of functions used for unification */
    /* These functions are defined in unify.cpp */
    theta unification(pred x, pred y, theta sub_list);
    theta unify_func(func x, func y, theta sub_list);
    theta unify_var(func x, func y, theta sub_list);
    vector<vector<uint>> unify_arg(uint x, uint y, vector<vector<uint>> sub_list);
    theta sub_var(func x, func y, theta sub_list); // x is assumed to be a variable
    theta sub_const(func x, func y, theta sub_list); // x is assumed to be a constant

    /* Set of functions used for resolution */
    /* These functions are defined in resolve.cpp */
    uint input_resolution_bfs(clause query);
    cnf resolve(clause c_i, clause c_j);
    void print_tautology(clause c, uint i);
    void print_contradiction(clause c, uint i);
    void print_resolution(clause c1, clause c2, uint i);
    void print_result(clause c, uint i);

    /* Set of functions dealing with negated predicates */
    bool is_neg(pred p);
    cnf negate_clause(clause c);

    /* Set of functions to apply a substitution to a logical expression */
    clause apply_sub_to_clause(clause c, vector<func> sub);
    pred apply_sub_to_pred(pred p, vector<func> sub);
    pred_args apply_sub_to_pred_args(pred_args pa, vector<func> sub);
    func apply_sub_to_func(func f, vector<func> sub);

    /* Set of functions to determine if two logical expressions are equal */
    bool clause_eq(clause f, clause g);
    bool pred_eq(pred f, pred g);
    bool pred_args_eq(pred_args f, pred_args g);
    bool func_eq(func f, func g);
    bool func_args_eq(func f, func g);

    /* Set of functions for combining AST logical expressions */
    cnf concat_cnf(cnf c1, cnf c2);
    cnf add_clause(cnf kb, clause c);
    clause concat_clause(clause c1, clause c2);
    cnf union_cnf(cnf c1, cnf c2);
    bool subset(cnf c1, cnf c2);

    /* C++ function set to print the members of the AST */
    void print_kb(ofstream *s, cnf kb);
    void print_clause(ofstream *s, clause c);
    void print_pred(ofstream *s, pred p);
    void print_pred_args(ofstream* s, pred_args pa);
    void print_func(ofstream *s, func f);
    void print_func_args(ofstream *s, func_args fa);

    /* C++ function set to build members of the AST */
    func build_func(uint function, func_args args);
    func build_fvar(uint arg);
    func build_fconst(uint arg);
    func build_fcardinal(uint dir, uint x, uint y);
    pred build_pred(uint predicate, pred_args args);

    /* Set of functions for evaluating logical functions */
    clause eval_clause(clause c);
    pred eval_pred(pred c);
    pred_args eval_pred_args(pred_args pa);
    pred_arg eval_func(func f);

    /* This set of functions returns a list of the constant 2D points within */
    vector<apoint> get_points_clause(clause c);
    vector<apoint> get_points_pred(pred p);
    vector<apoint> get_points_pred_args(pred_args pa);
    vector<apoint> get_points_func(func f);
    vector<apoint> get_points_func_args(func_args fa);

    /* These functions are used to access members of the AST */
    pred_name p_name(pred p);
    pred_args p_args(pred p);
    pred_arg p_argi(pred p, uint index);
    func_name f_name(func f);
    func_args f_args(func f);
    func_arg f_argi(func f, uint index);

    /* Functions to convert from the format of the 2D points of the AST */
    /* and Point objects */
    apoint position_to_bits(Point * position);
    Point bits_to_position(apoint bits);
};




#endif /* KNOWLEDGE_H */

