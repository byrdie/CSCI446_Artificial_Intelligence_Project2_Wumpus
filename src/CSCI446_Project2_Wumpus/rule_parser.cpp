/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "rule_parser.h"

void  parse() 
{   
    cnf rules;
    
    
    vector <vector<tuple<int, vector<tuple<int, vector<int> > > > > >  conjuncts;
    ifstream file("test.txt");
    string str; 
    vector<pred> predicates;
    while (getline(file, str ))
    {   
       cnf.push_back(predicate(str));
            
        
    }
}

vector<pred> predicate(string str){
    
}

