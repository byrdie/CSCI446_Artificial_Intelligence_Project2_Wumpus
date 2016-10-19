
#include "knowledge.h"
#include <typeinfo>

Knowledge::Knowledge() {

    rule_parser = new RuleParser();
    static_kb = rule_parser->parse_cnf();

    func_inv[F_CONST] = F_CONST;
    func_inv[F_VAR] = F_VAR;
    func_inv[F_NORTH] = F_SOUTH;
    func_inv[F_SOUTH] = F_NORTH;
    func_inv[F_EAST] = F_WEST;
    func_inv[F_WEST] = F_EAST;

}

theta Knowledge::unification(pred x, pred y, theta sub_list) {
    pred_args x_args = get<1>(x);
    pred_args y_args = get<1>(y);


    /* Check that the same predicates are used and the same number of arguments are used. */
    if ((get<0>(x) != get<0>(y)) || (x_args.size() != y_args.size())) {
        return sub_list;
    }

    /*  */
    //    for (uint i = 0; i < get<1>(x).size(); i++) {
    //        //if (get<0>(get<1>(x)[i]) != get<0>(get<1>(y)[i])) {
    //        //    return sub_list;
    //        // }
    //        func x_func = get<1>(x)[i];
    //        func y_func = get<1>(y)[i];
    //        x_args.push_back(x_func);
    //        y_args.push_back(y_func);
    //    }

    for (uint i = 0; i < x_args.size(); i++) {
        sub_list = unify_func(x_args[i], y_args[i], sub_list);
    }
    return sub_list;
}

theta Knowledge::unify_func(func f, func g, theta sub_list) {

    int f_name = get<0>(f);
    int g_name = get<0>(g);

    func_args f_args = get<1>(f);
    func_args g_args = get<1>(g);

    /* Logic for unifying a constant, function or variable */
    if (f_name == F_CONST) { // f is a constant
        if (g_name == F_CONST) { // f and g are constants

            // Not sure what to do here, obviously only works if f == g
            cout << "Undefined function!" << endl;

        } else if (g_name == F_VAR) { // f is a constant, g is a variable

            cout << "Undefined function!" << endl;

        } else { // f is a constant, g is a function

            cout << "Undefined function!" << endl;

        }

    } else if (f_name == F_VAR) { // f is a variable
        if (g_name == F_CONST) { // f is a variable, g is a constant

            cout << "Undefined function!" << endl;

        } else if (g_name == F_VAR) { // f and g are variables

            /* Unify variables and build a new function */
            sub_list = unify_var2(f, g, sub_list);
            if (sub_list.empty()) {
                return sub_list;
            }
        } else { // f is a variable, g is a function
            vector<func> sub;
            sub.push_back(f);
            sub.push_back(g);
            sub_list.push_back(sub);
        }
    } else { // f is a function
        if (g_name == F_CONST) { // f is a function, g is a constant
            cout << "Undefined function!" << endl;
        } else if (g_name == F_VAR) { // f is a function, g is a variable
            vector<func> sub;
            sub.push_back(g);
            sub.push_back(f);
            sub_list.push_back(sub);
        } else { // f and g are functions
            cout << "Undefined function!" << endl;

        }
    }
    return sub_list;
}

theta Knowledge::unify_var2(func x, func y, theta sub_list) {

    theta sub_list_copy = sub_list;     // Copy the list so we can add to is as we iterate

    /* Check if x or y is already in the sublist */
    for (uint i = 0; i < sub_list_copy.size(); i++) {

        func tfunc = sub_list_copy[i][0];
        func sfunc = sub_list_copy[i][1];

        /* Check to see if we already have a substitution for this variable */
        if (func_eq(x, tfunc)) { // Full function substitution
            x = sfunc;
        } else if (func_args_eq(x, sfunc)) { // argument substitution


            func sub = sfunc;
            vector<func> subsub_list;

            /* attempt to unify by inverting function */
            int inverse = func_inv[get<0>(sub)];
            if (inverse != 0) { // inverse exists
                get<0>(sub) = inverse;
                subsub_list.push_back(x);
                subsub_list.push_back(sub);
                sub_list.push_back(subsub_list);
                x = sub;
            } else {
                theta empty_list;
                return empty_list;
            }

        }
        if (func_eq(y, tfunc)) { // Full function substitution
            y = sfunc;
        } else if (func_args_eq(y, sfunc)) { // argument substitution

            func sub = sfunc;
            vector<func> subsub_list;

            /* attempt to unify by inverting function */
            int inverse = func_inv[get<0>(sub)];
            if (inverse != 0) { // inverse exists
                get<0>(sub) = inverse;
                subsub_list.push_back(y);
                subsub_list.push_back(sub);
                sub_list.push_back(subsub_list);
                y = sub;
            } else {
                theta empty_list;
                return empty_list;
            }
        }

    }

    int xname = get<0>(x);
    int yname = get<0>(y);

    /* Attempt unification if no substitution has been provided for x or y */
    if (func_eq(x, y)) {
        vector<func> subsub_list;
        subsub_list.push_back(x);
        subsub_list.push_back(y);
        sub_list.push_back(subsub_list);
    } else if (xname == F_VAR) {
        vector<func> subsub_list;
        subsub_list.push_back(x);
        subsub_list.push_back(y);
        sub_list.push_back(subsub_list);
    } else if (yname == F_VAR) {
        vector<func> subsub_list;
        subsub_list.push_back(y);
        subsub_list.push_back(x);
        sub_list.push_back(subsub_list);
    } else {
        theta empty_list;
        return empty_list;
    }
    return sub_list;

}

vector<vector<uint>> Knowledge::unify_var(uint x, uint y, vector<vector<uint>> sub_list) {
    cout << x << ", " << y << endl;
    //check if x or y are already in the the sublist
    for (uint i = 0; i < sub_list.size(); i++) {
        if (x == sub_list[i][0]) {
            x = sub_list[i][1];
        }
        if (y == sub_list[i][0]) {
            y = sub_list[i][1];
        }
    }
    if (x == y) {
        vector<uint> s_sub_list;
        s_sub_list.push_back(x);
        s_sub_list.push_back(y);
        sub_list.push_back(s_sub_list);

    } else if ((x & A_CONST) == 0) {
        vector<uint> s_sub_list;
        s_sub_list.push_back(x);
        s_sub_list.push_back(y);
        sub_list.push_back(s_sub_list);

    } else if ((y & A_CONST) == 0) {
        vector<uint> s_sub_list;
        s_sub_list.push_back(y);
        s_sub_list.push_back(x);
        sub_list.push_back(s_sub_list);

    } else {
        vector<vector < uint>> list;
        return list;
    }
    return sub_list;
}

/**
 * Resolve returns the set of all possible clauses obtained by resolving the
 * two inputs ci and cy
 * @param ci
 * @param cj
 * @return a set fo resolved clauses
 */
cnf Knowledge::resolve(clause ci, clause cj) {

    cnf resolvents; // Allocate space for the new formulae

    /* Loop through every literal in both clauses */
    for (uint i = 0; i < ci.size(); i++) {
        for (uint j = 0; j < cj.size(); j++) {

            /* Select the next two predicates */
            pred pi = ci[i];
            pred pj = cj[j];

            /* Check that one (not both) of the objects are negated */
            if (is_neg(pi) xor is_neg(pj)) {

                theta sub_list; // theta is a list of substitutions
                sub_list = unification(pi, pj, sub_list); // Attempt to unify the two predicates

                /* Check if the unification process succeeded before continuing */
                if (!sub_list.empty()) { // Substitution is non-empty

                    /* Make a copy of the input clauses to modify */
                    clause ci_copy = ci;
                    clause cj_copy = cj;

                    /* delete the predicates from their respective clauses */
                    ci_copy.erase(ci_copy.begin() + i);
                    cj_copy.erase(cj_copy.begin() + j);

                    /* A resolvent is a union of the clauses after resolution */
                    clause union_c = concat_clause(ci_copy, cj_copy);

                    /* Apply the list of substitutions */
                    for (uint k = 0; k < sub_list.size(); k++) {

                        union_c = apply_sub_to_clause(union_c, sub_list[k]);

                    }

                    /* Add the new resolvent to the list of resolvents */
                    resolvents.push_back(union_c);
                }
            }

        }
    }
    return resolvents;
}

bool Knowledge::resolution(cnf kb, clause query) {

    kb = concat_cnf(kb, negate_clause(query));

    cnf new_k; // Empty space to store the proposed knowledge

    /* For each pair of clauses in clauses */
    for (uint i = 0; i < kb.size(); i++) {
        for (uint j = 0; j < kb.size(); j++) {

            if (i != j) { // Don't try and resolve a clause with itself
                cnf resolvents = resolve(kb[i], kb[j]); // Find all possible resolvents of the pair of clauses

                /* If resolvents contains the empty clause then return true */
                for (uint k = 0; k < resolvents.size(); k++) {
                    if (resolvents.empty()) {
                        return true;
                    }
                }
                
                 new_k = union_cnf(new_k, resolvents);
                
            }
            
            
        }
    }
    
    
}

bool Knowledge::is_neg(pred p) {
    if ((get<0>(p) & P_NEGATION) > 0) {
        return true;
    } else {
        return false;
    }
}

cnf Knowledge::negate_clause(clause c) {

    cnf ret;
    for (uint i = 0; i < c.size(); i++) {
        clause ret_c;
        pred p;
        get<0>(p) = get<0>(p) | P_NEGATION;
        ret_c.push_back(p);
    }


    return ret;

}

/**
 * Apply a substitution provided by the unification algorithm
 * Please note that this modifies the provided clause, If you value your life, 
 * you will not call this function with the master knowledge base.
 * @param c
 * @param 
 * @return the clause with substitutions applied.
 */
clause Knowledge::apply_sub_to_clause(clause c, vector<func> sub) {
    for (uint j = 0; j < c.size(); j++) {
        c[j] = apply_sub_to_pred(c[j], sub);
    }
    return c;
}

pred Knowledge::apply_sub_to_pred(pred p, vector<func> sub) {
    get<1>(p) = apply_sub_to_pred_args(get<1>(p), sub);
    return p;
}

pred_args Knowledge::apply_sub_to_pred_args(pred_args pa, vector<func> sub) {
    for (uint k = 0; k < pa.size(); k++) {
        pa[k] = apply_sub_to_func(pa[k], sub);
    }
    return pa;
}

func Knowledge::apply_sub_to_func(func f, vector<func> sub) {

    /* Two functions are the same if the hash is the same  */
    if (func_eq(f, sub[0])) {
        f = sub[1];
    }
    return f;

}

bool Knowledge:: clause_eq(clause f, clause g){
    if(f.size() == g.size()){
        for(uint i = 0; i < f.size(); i++){
                if(!pred_eq(f[i], g[i])){
                    return false;
                }
        }
        return true;
    } else{
        return false;
    }
}
bool Knowledge::pred_eq(pred f, pred g){
    if(get<0>(f) == get<0>(g)){
        if(pred_args_eq(get<1>(f), get<1>(g))){
            return true;
        }
    } else{
        return false;
    }
    
}

bool Knowledge::pred_args_eq(pred_args f, pred_args g){
    if(f.size() == g.size()){
        for(uint i = 0; i < f.size(); i++){
                if(!func_eq(f[i], g[i])){
                    return false;
                }
        }
        return true;
    } else{
        return false;
    }
    
}

bool Knowledge::func_eq(func f, func g) {
    if (get<0>(f) == get<0>(g)) {
        return func_args_eq(f, g);
    } else {
        return false;
    }
}



bool Knowledge::func_args_eq(func f, func g) {
    func_args f_args = get<1>(f);
    func_args g_args = get<1>(g);
    if (f_args.size() == g_args.size()) {
        for (uint i = 0; i < f_args.size(); i++) {
            if (f_args[i] != g_args[i]) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

/**
 * Returns the combination of two lists of clauses
 * @param c1    The first list of clauses
 * @param c2    The second list of clauses
 * @return      The combined list of clauses
 */
cnf Knowledge::concat_cnf(cnf c1, cnf c2) {

    for (uint i = 0; i < c2.size(); i++) {
        c1.push_back(c2[i]);
    }

    return c1;
}

clause Knowledge::concat_clause(clause c1, clause c2) {

    for (uint i = 0; i < c2.size(); i++) {
        c1.push_back(c2[i]);
    }

    return c1;
}

cnf Knowledge :: union_cnf(cnf c1, cnf c2){
    cnf new_cnf = c2;
    
    for(uint i =0;  i < c1.size(); i++){
        bool flag = false;
        for(uint j = 0; j < c2.size(); j++){
            if(clause_eq(c1[i], c2[j])){
                flag = true;
            }
        }
        if(!flag){
            c2.push_back(c1[i]);
        }
    }
    return new_cnf;
}



/**
 * Series of function to print out a knowledge base for viewing
 * @param kb
 */
void Knowledge::print_kb(cnf kb) {
    for (uint i = 0; i < kb.size(); i++) {
        print_clause(kb[i]);
        cout << endl;
    }
}

void Knowledge::print_clause(clause c) {
    for (uint j = 0; j < c.size(); j++) {
        print_pred(c[j]);
        if (j != (c.size() - 1)) {
            cout << " || ";
        }
    }
}

void Knowledge::print_pred(pred p) {

    int pred_tok = get<0>(p);

    if (pred_tok & P_NEGATION) {
        cout << "~";
        pred_tok = pred_tok & P_UNNEGATION;
    }

    string pred_name = rule_parser->pred_str_map[pred_tok];
    cout << pred_name;
    cout << "(";
    print_pred_args(get<1>(p));
    cout << ")";
}

void Knowledge::print_pred_args(pred_args pa) {

    for (uint k = 0; k < pa.size(); k++) {
        print_func(pa[k]);
        if (k != (pa.size() - 1)) {
            cout << ", ";
        }
    }
}

void Knowledge::print_func(func f) {
    int func_tok = get<0>(f);

    if (func_tok == F_VAR or func_tok == F_CONST) {
        func_args fa = get<1>(f);
        cout << fa[0];
    } else {
        string func_name = rule_parser->func_str_map[func_tok];
        cout << func_name;
        cout << "(";
        print_func_args(get<1>(f));
        cout << ")";
    }
}

void Knowledge::print_func_args(func_args fa) {

    for (uint l = 0; l < fa.size(); l++) {
        cout << fa[l];
        if (l != fa.size() - 1) {
            cout << ",";
        }
    }
}
func Knowledge::build_func(uint function, func_args args){
    func return_func;
    if(function == F_VAR || function == F_CONST){
        if (args.size() > 1){
            cout <<"WARNING: Invalid function arguments" << endl;
        }
    }
    get<0>(return_func) = function;
    get<1>(return_func) = args;
    return return_func;
    
    
}
pred Knowledge::build_pred(uint predicate, pred_args args){
    pred return_pred;
    get<0>(return_pred) = predicate;
    get<1>(return_pred) = args;
    return return_pred;
}