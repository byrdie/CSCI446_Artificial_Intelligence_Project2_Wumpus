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
#include <string.h>
#include <algorithm>

#include "knowledge.h"

using namespace std;
//typedef vector <vector<tuple<int, vector<tuple<int, vector<int> > > > > >  cnf;
//typedef vector<tuple<int, vector<tuple<int, vector<int> > > > >         clause;
//typedef tuple<int, vector<tuple<int, vector<int> > > >                    pred;
//typedef vector<tuple<int, vector<int> > >                                funcs;
//typedef tuple<int, vector<int> >                                          func;

cnf         parse_cnf();
clause      parse_clause(string str, int * index);
pred        parse_pred(string str, int * index);
pred_args   parse_pred_args(string str, int * index);
func        parse_func(string str, int * index);
func_args   parse_func_args(string str, int * index);

int find_next_delim(string str, int * index);
#endif /* RULE_PARSER_H */

