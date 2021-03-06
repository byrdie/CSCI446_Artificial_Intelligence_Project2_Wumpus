/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "rule_parser.h"

RuleParser::RuleParser() {

    num_var = 1;
    initialize_token_map();

}

cnf RuleParser::parse_cnf(string filename) {
    cnf rules;


    vector <vector<tuple<int, vector<tuple<int, vector<int> > > > > > conjuncts;
    ifstream file(filename);
    string str;
    while (getline(file, str)) {
        if (str.length() == 0) {
            continue;
        }
        int index = 0;
        rules.push_back(parse_clause(str, &index));
    }

    return rules;
}

clause RuleParser::parse_clause(string str, int * index) {

    sym_map.clear(); // Delete all entries in the symbol table for a new row

    clause ret_clause;

    while (true) {
        ret_clause.push_back(parse_pred(str, index));

        char cur_char = str[*index];
        if (cur_char == ',') {
            char next_char = str[*index + 1];
            if (next_char == ',') {
                return ret_clause;
            } else {
                *index = *index + 1; // Increment the cursor
                continue;
            }
        } else {
            *index = *index + 1; // Increment the cursor
            cout << "SYNTAX ERROR: 'parse_clause', index at wrong position or no endline detected" << endl;
        }
    }
}

pred RuleParser::parse_pred(string str, int * index) {

    int begin = *index; // Save the location of where we started 
    int d_i = find_next_delim(str, index); // Find index of next delimiter
    *index = d_i + 1; // Move the index to the next space after the delimiter
    char next_d = str[d_i]; // Find value of the next delimiter

    pred ret_pred; // allocate space for return predicate   
    if (next_d == '[') { // The next terms are arguments for the predicate

        get<1>(ret_pred) = parse_pred_args(str, index);

        int neg = 0;
        if (str[begin] == '!') { // predicate is negated
            neg = P_NEGATION;
            begin = begin + 1;
        }

        string pred_str = str.substr(begin, d_i - begin); // Pick the function name out of the total string
        if (pred_tok_map.find(pred_str) == pred_tok_map.end()) {
            cout << "SYNTAX ERROR: 'parse_pred', predicate name not recognized" << endl;
            get<0>(ret_pred) = 0;
        } else {
            get<0>(ret_pred) = (pred_tok_map[pred_str] | neg); // negate the predicate if necessary
        }

    } else if (next_d == ',') {
        cout << "Syntax Error in 'parse_pred', early comma detected" << endl;
    } else if (next_d == ']') {
        cout << "Syntax Error in 'parse_pred', early closing brace detected" << endl;
    }

    return ret_pred;
}

pred_args RuleParser::parse_pred_args(string str, int * index) {

    pred_args ret_pred_args;

    while (true) {
        ret_pred_args.push_back(parse_func(str, index)); // index should be after the closing brace for function

        char cur_char = str[*index];
        if (cur_char == ',') {
            *index = *index + 1;
            continue;
        } else if (cur_char == ']') {
            *index = *index + 1;
            return ret_pred_args;
        } else {
            *index = *index + 1;
            cout << "SYNTAX ERROR: 'parse_pred_args' missing closing brace" << endl;
            return ret_pred_args;
        }
    }
}

func RuleParser::parse_func(string str, int * index) {

    int begin = *index; // Save the location of where we started 
    int d_i = find_next_delim(str, index); // Find index of next delimiter

    char next_d = str[d_i]; // Find value of the next delimiter

    func ret_func; // allocate space for return function   
    if (next_d == '[') { // The next terms are arguments for the function
        *index = d_i + 1; // Move the index to the next space after the delimiter
        get<1>(ret_func) = parse_func_args(str, index);

        string func_str = str.substr(begin, d_i - begin); // Pick the function name out of the total string
        if (func_tok_map.find(func_str) == func_tok_map.end()) {
            cout << "SYNTAX ERROR: 'parse_func', function name not recognized" << endl;
            get<0>(ret_func) = 0;
        } else {
            get<0>(ret_func) = func_tok_map[func_str];

        }

    } else if (next_d == ']' or next_d == ',') { // This is a variable

        func_args var_args;
        var_args.push_back(parse_arg(str, index)); // Read in argument
        get<0>(ret_func) = F_VAR; // Variables use the identity function
        get<1>(ret_func) = var_args;

    } else {
        cout << "SYNTAX ERROR: 'parse_func', no detectable delimiter" << endl;
    }

    return ret_func;

}

func_args RuleParser::parse_func_args(string str, int * index) {

    func_args ret_func_args;

    while (true) {
        ret_func_args.push_back(parse_arg(str, index));


        char cur_char = str[*index];
        if (cur_char == ',') {
            *index = *index + 1; // Move to the next argument
            continue;
        } else if (cur_char == ']') {
            *index = *index + 1; // Move up one level
            return ret_func_args;
        } else {
            *index = *index + 1; // Move up one level
            cout << "SYNTAX ERROR: 'parse_func_args' missing closing brace" << endl;
            return ret_func_args;
        }
    }
}

int RuleParser::parse_arg(string str, int* index) {

    char next_var = str[*index]; // Get the next symbol
    *index = *index + 1; // Increment cursor

    while (next_var == ' ') {
        next_var = str[*index]; // Get the next symbol
        *index = *index + 1; // Increment cursor
    }

    if (next_var == '[' or next_var == ']' or next_var == ',') {
        cout << "SYNTAX ERROR: 'parse_arg', assigning delimiter as variable" << endl;
    }

    if (sym_map.find(next_var) == sym_map.end()) { // Symbol not in table

        sym_map[next_var] = num_var; // Add symbol to table
        num_var++; // Increment the number of variables

    }
    return sym_map[next_var]; // return value of the symbol table

}

int RuleParser::find_next_delim(string str, int * index) {
    vector<int> delims;

    int ob = str.find("[", *index);
    int com = str.find(",", *index);
    int cb = str.find("]", *index);

    if (ob > -1) {
        delims.push_back(ob);
    }
    if (com > -1) {
        delims.push_back(com);
    }
    if (cb > -1) {
        delims.push_back(cb);
    }

    return *min_element(begin(delims), end(delims));
}

void RuleParser::initialize_token_map() {
    pred_tok_map["Breezy"] = P_BREEZY;
    pred_tok_map["Pit"] = P_PIT;
    //    pred_tok_map["Safe"] = P_SAFE;
    pred_tok_map["Wall"] = P_WALL;
    //    pred_tok_map["Stench"] = P_STENCH;
    //    pred_tok_map["Breeze"] = P_BREEZE;
    pred_tok_map["Stinky"] = P_STINKY;
    pred_tok_map["Wumpus"] = P_WUMPUS;

    pred_tok_map["Explored"] = P_EXPLORED;

    pred_tok_map["IsClear"] = P_ISCLEAR;
    pred_tok_map["AdjExplored"] = P_ADJEXPLORED;

    pred_tok_map["StepForward"] = P_STEPFORWARD;
    pred_tok_map["TurnRight"] = P_TURNRIGHT;
    pred_tok_map["TurnLeft"] = P_TURNLEFT;


    pred_tok_map["Agent"] = P_AGENT;

    pred_tok_map["MaxX"] = P_MAXX;
    pred_tok_map["MaxY"] = P_MAXY;
    pred_tok_map["MinX"] = P_MINX;
    pred_tok_map["MinY"] = P_MINY;


    func_tok_map["north"] = F_NORTH;
    func_tok_map["south"] = F_SOUTH;
    func_tok_map["east"] = F_EAST;
    func_tok_map["west"] = F_WEST;

    func_tok_map["right"] = F_RIGHT;
    func_tok_map["left"] = F_LEFT;
    func_tok_map["forward"] = F_FORWARD;
    func_tok_map["backward"] = F_BACKWARD;
    func_tok_map["getX"] = F_GETX;
    func_tok_map["getY"] = F_GETY;



    pred_str_map[P_BREEZY] = "Breezy";
    pred_str_map[P_PIT] = "Pit";
    //    pred_str_map[P_SAFE] = "Safe";
    pred_str_map[P_WALL] = "Wall";
    //    pred_str_map[P_STENCH] = "Stench";
    //    pred_str_map[P_BREEZE] = "Breeze";
    pred_str_map[P_STINKY] = "Stinky";
    pred_str_map[P_WUMPUS] = "Wumpus";

    pred_str_map[P_EXPLORED] = "Explored";

    pred_str_map[P_ISCLEAR] = "IsClear";
    pred_str_map[P_ADJEXPLORED] = "AdjExplored";
    pred_str_map[P_AGENT] = "Agent";

    pred_str_map[P_STEPFORWARD] = "StepForward";
    pred_str_map[P_TURNRIGHT] = "TurnRight";
    pred_str_map[P_TURNLEFT] = "TurnLeft";
    
    pred_str_map[P_MAXX] = "MaxX";
    pred_str_map[P_MAXY] = "MaxY";
    pred_str_map[P_MINX] = "MinX";
    pred_str_map[P_MINY] = "MinY";

    func_str_map[F_NORTH] = "north";
    func_str_map[F_SOUTH] = "south";
    func_str_map[F_EAST] = "east";
    func_str_map[F_WEST] = "west";

    func_str_map[F_RIGHT] = "right";
    func_str_map[F_LEFT] = "left";
    func_str_map[F_FORWARD] = "forward";
    func_str_map[F_BACKWARD] = "backward";
    
    func_str_map[F_GETX] = "getX";
    func_str_map[F_GETY] = "getY";


}
