
#include "knowledge.h"
#include <typeinfo>
Knowledge::Knowledge() {

    rule_parser = new RuleParser();
    static_kb = rule_parser->parse_cnf();

}

theta Knowledge::unification(pred x, pred y, theta sub_list) {
    pred_args x_args;
    pred_args y_args;
    
    
    //Check that the same predicates are used and the same number of arguments are used.
    if ((get<0>(x) != get<0>(y)) || (get<1>(x).size() != get<1>(y).size())) {
        cout << get<0>(x) <<"\n";
        cout << get<0>(y) <<"\n\n";
        
        return sub_list;
    }
    
    //checks that the same functions are used
    for (uint i = 0; i < get<1>(x).size(); i++) {
        //if (get<0>(get<1>(x)[i]) != get<0>(get<1>(y)[i])) {
        //    return sub_list;
       // }
        func x_func = get<1>(x)[i];
        func y_func = get<1>(y)[i];
        x_args.push_back(x_func);
        y_args.push_back(y_func);
    }
    
    for (uint i = 0; i < x_args.size(); i++) {
        func_args x_vars = get<1>(x_args[i]);
        func_args y_vars = get<1>(y_args[i]);
        
        for (uint j = 0; j < x_vars.size(); j++){
            
            sub_list = unify_var(x_vars[j], y_vars[j], sub_list);
            if (sub_list.size() == 0){
                return sub_list;
            }
        }
    }
    return sub_list;
}
theta Knowledge :: unify_func(func x, func y, theta sub_list){
    //Do regular check like formula
    if(get<0>(x) == F_IDENTITY && get<0>(y) == F_IDENTITY){
        ;
    }else if(get<0>(x) == F_IDENTITY){
        //replace x with y func
        ;
    }else if(get<0>(y) == F_IDENTITY){
        //replace y with func
        ;
    }else{
        //unify func args
        ;
    }
    return sub_list;
}

theta Knowledge :: unify_var(uint x, uint y, theta sub_list){
    //check if x or y are already in the the sublist
    for (uint i = 0; i < sub_list.size(); i++){
        if (x = sub_list[i][0]){
            x = sub_list[i][1];
        }
        if (y = sub_list[i][0]){
            y = sub_list[i][1];
        }
    }
    if (x == y){
        vector<uint> s_sub_list;
        s_sub_list.push_back(x);
        s_sub_list.push_back(y);
        sub_list.push_back(s_sub_list);
        
    }else if(x & A_CONST == 0){
        vector<uint> s_sub_list;
        s_sub_list.push_back(x);
        s_sub_list.push_back(y);
        sub_list.push_back(s_sub_list);
        
    }else if(y & A_CONST == 0){
        vector<uint> s_sub_list;
        s_sub_list.push_back(y);
        s_sub_list.push_back(x);
        sub_list.push_back(s_sub_list);
        
    }else{
        theta list;
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
clause Knowledge::apply_sub_to_clause(clause c, vector<uint> sub) {
    for (uint j = 0; j < c.size(); j++) {
        c[j] = apply_sub_to_pred(c[j], sub);
    }
    return c;
}

pred Knowledge::apply_sub_to_pred(pred p, vector<uint> sub) {
    get<1>(p) = apply_sub_to_pred_args(get<1>(p), sub);
    return p;
}

pred_args Knowledge::apply_sub_to_pred_args(pred_args pa, vector<uint> sub) {
    for (uint k = 0; k < pa.size(); k++) {
        pa[k] = apply_sub_to_func(pa[k], sub);
    }
    return pa;
}

func Knowledge::apply_sub_to_func(func f, vector<uint> sub) {

    get<1>(f) = apply_sub_to_func_args(get<1>(f), sub);
    return f;

}

func_args Knowledge::apply_sub_to_func_args(func_args fa, vector<uint> sub) {

    uint cur_arg;
    uint test_arg = sub[0];

    for (uint l = 0; l < fa.size(); l++) {
        cur_arg = fa[l];
        if (cur_arg == test_arg) {
            fa[l] = sub[1];
        }
    }
    return fa;

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

/**
 * Series of functions to make a copy of a knowledge base
 * @param kb
 * @return 
 */
cnf Knowledge::copy_kb(cnf kb) {
    cnf kb_copy;
    for (uint i = 0; i < kb.size(); i++) {
        kb_copy.push_back(copy_clause(kb[i]));
    }
    return kb_copy;
}

clause Knowledge::copy_clause(clause c) {
    clause c_copy;
    for (uint j = 0; j < c.size(); j++) {
        c_copy.push_back(copy_pred(c[j]));
    }
    return c_copy;
}

pred Knowledge::copy_pred(pred p) {
    pred p_copy;
    get<0>(p_copy) = get<0>(p);
    get<1>(p_copy) = copy_pred_args(get<1>(p));
    return p_copy;

}

pred_args Knowledge::copy_pred_args(pred_args pa) {
    pred_args pa_copy;
    for (uint k = 0; k < pa.size(); k++) {
        pa_copy.push_back(copy_func(pa[k]));
    }
    return pa_copy;
}

func Knowledge::copy_func(func f) {
    func f_copy;
    get<0>(f_copy) = get<0>(f);
    get<1>(f_copy) = copy_func_args(get<1>(f));
    return f_copy;
}

func_args Knowledge::copy_func_args(func_args fa) {
    func_args fa_copy;
    for (uint l = 0; l < fa.size(); l++) {
        fa_copy.push_back(fa[l]);
    }
    return fa_copy;
}

/**
 * Series of functions to delete knowledge bases after we are finished with them
 * @param kb
 */
void Knowledge::del_kb(cnf kb) {
    for (uint i = 0; i < kb.size(); i++) {
        del_clause(kb[i]);
    }
    kb.clear();
}

void Knowledge::del_clause(clause c) {
    for (uint j = 0; j < c.size(); j++) {
        del_pred(c[j]);
    }
    c.clear();
}

void Knowledge::del_pred(pred p) {
    del_pred_args(get<1>(p));
}

void Knowledge::del_pred_args(pred_args pa) {
    for (uint k = 0; k < pa.size(); k++) {
        del_func(pa[k]);
    }
    pa.clear();
}

void Knowledge::del_func(func f) {
    del_func_args(get<1>(f));
}

void Knowledge::del_func_args(func_args fa) {
    fa.clear();
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

    if (func_tok == F_IDENTITY) {
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
