/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "rule_parser.h"

cnf parse_cnf() 
{   
    cnf rules;
    
    
    vector <vector<tuple<int, vector<tuple<int, vector<int> > > > > >  conjuncts;
    ifstream file("../Rules/test.txt");
    string str; 
    while (getline(file, str))
    {   
        int index = 0
        rules.push_back(parse_clause(str,&index));     
    }
}

clause parse_clause(string str, int * index){
    
    clause ret_clause;
    
    while(true){
        ret_clause.push_back(parse_pred(str, index));
        
        char cur_char = str[*index];
        if(cur_char == ','){
            char next_char = str[*index + 1];
            if(next_char == ','){
                return ret_clause;
            } else {
                continue;
            }
        } else {
            cout << "SYNTAX ERROR: 'parse_clause', index at wrong position or no endline detected" << endl;
        }
    }
}

pred parse_pred(string str, int * index){
    
    int begin = *index;     // Save the location of where we started 
    int d_i = find_next_delim(str, index);  // Find index of next delimiter
    *index += d_i + 1;   // Move the index to the next space after the delimiter
    char next_d = str[d_i];         // Find value of the next delimiter
    
    pred ret_pred;      // allocate space for return predicate   
    if (next_d == '['){      // The next terms are arguments for the predicate
        
        get<1>(ret_pred) = parse_pred_args(str, index);
        
    } else if (next_d == ','){
        cout << "Syntax Error in 'parse_pred', early comma detected" << endl;
    } else if (next_d == ']'){
        cout << "Syntax Error in 'parse_pred', early closing brace detected" << endl;
    }
    
    return ret_pred;
}

pred_args parse_pred_args(string str, int * index){
    
    int begin = *index;     // Save the location of where we started 
    int d_i = find_next_delim(str, index);  // Find index of next delimiter
//    *index += d_i + 1;   // Move the index to the next space after the delimiter
    char next_d = str[d_i];         // Find value of the next delimiter
    
    pred_args ret_pred_args;
    
    if (next_d == '['){     // This argument is a function
        
        ret_pred_args.push_back(parse_func(str, index));    // index should be after the closing brace for function
        
    } else if (next_d == ','){      // There are multiple arguments to this predicate 
        
        
        
    } else if (next_d == ']'){      // This argument is a variable
        
        
        
    }
}

func parse_func(string str, int * index){
    
    
    
}

int find_next_delim(string str, int * index){
    vector<int> delims;
    delims.push_back(str.find("[",*index));
    delims.push_back(str.find(",",*index));
    delims.push_back(str.find("]"));
    
    return *min_element(begin(delims),end(delims));
}
