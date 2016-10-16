/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rule_parser.h
 * Author: byrdie
 *
 * Created on October 16, 2016, 5:40 PM
 */

#ifndef RULE_PARSER_H
#define RULE_PARSER_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>


using namespace std;
//typedef vector <vector<tuple<int, vector<tuple<int, vector<int> > > > > >  cnf;
//typedef vector<tuple<int, vector<tuple<int, vector<int> > > > >         clause;
//typedef tuple<int, vector<tuple<int, vector<int> > > >                    pred;
//typedef vector<tuple<int, vector<int> > >                                funcs;
//typedef tuple<int, vector<int> >                                          func;
typedef vector<int>             func_args;  // integer represents function parameters, variable index, or constant value
typedef tuple<int, func_args>   func;       // integer represents function name, variable type, or constant type
typedef vector<func>            pred_args;  // Arguments to predicates
typedef tuple<int, pred_args>   pred;       // Integer represents predicate name
typedef vector<vector<pred>>    cnf;        // CNF representation of all predicates

void parse();
#endif /* RULE_PARSER_H */

