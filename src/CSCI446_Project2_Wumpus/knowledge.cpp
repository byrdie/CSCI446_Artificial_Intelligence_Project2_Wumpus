
#include "knowledge.h"

Knowledge::Knowledge() {

    rule_parser = new RuleParser();
    static_kb = rule_parser->parse_cnf();

}

bool is_neg(pred p){
    if((p & P_NEGATION) > 0){
        return true;
    } else {
        return false;
    }
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
        c[j]=apply_sub_to_pred(c[j], sub);
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
cnf Knowledge::concat_kb(cnf c1, cnf c2) {

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