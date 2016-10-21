
#include "knowledge.h"
#include <typeinfo>

Knowledge::Knowledge(string filename) {

    rule_parser = new RuleParser();
    static_kb = rule_parser->parse_cnf(filename);
   

    func_inv[F_CONST] = F_CONST;
    func_inv[F_VAR] = F_VAR;
    func_inv[F_NORTH] = F_SOUTH;
    func_inv[F_SOUTH] = F_NORTH;
    func_inv[F_EAST] = F_WEST;
    func_inv[F_WEST] = F_EAST;


}

cnf Knowledge::negate_clause(clause c) {

    cnf ret;
    clause ret_c;
    for (uint i = 0; i < c.size(); i++) {

        pred p = c[i];
        get<0>(p) = get<0>(p) ^ P_NEGATION;
        ret_c.push_back(p);
    }
    ret.push_back(ret_c);


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

    /* Apply the substitution */
    if (func_eq(f, sub[0])) { // if possible, sub the whole function
        f = sub[1];
    } else if ((get<0>(sub[0]) == F_VAR) and (get<0>(sub[1]) < F_NORTH)) { // If we're subbing a variable for a variable or constant

        uint svar = get<1>(sub[0])[0];
        uint sval = get<1>(sub[1])[0];

        func_args fargs = get<1>(f);
        for (uint i = 0; i < fargs.size(); i++) {
            if (fargs[i] == svar) {
                fargs[i] = sval;
            }
        }
        get<1>(f) = fargs;

    }
    return f;

}

bool Knowledge::clause_eq(clause f, clause g) {
    if (f.size() == g.size()) {
        for (uint i = 0; i < f.size(); i++) {
            if (!pred_eq(f[i], g[i])) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool Knowledge::pred_eq(pred f, pred g) {
    if (get<0>(f) == get<0>(g)) {
        if (pred_args_eq(get<1>(f), get<1>(g))) {
            return true;
        }
    }
    return false;
}

bool Knowledge::pred_args_eq(pred_args f, pred_args g) {
    if (f.size() == g.size()) {
        for (uint i = 0; i < f.size(); i++) {
            if (!func_eq(f[i], g[i])) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }

}

bool Knowledge::func_eq(func f, func g) {

    uint fname = get<0>(f);
    uint gname = get<0>(g);

    if (fname == gname) {
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
        bool flag = false;
        for (uint j = 0; j < c1.size(); j++) {
            if (pred_eq(c1[j], c2[i])) {
                flag = true;
            }
        }
        if (!flag) {
            c1.push_back(c2[i]);
        }

    }

    return c1;
}

cnf Knowledge::union_cnf(cnf c1, cnf c2) {
    cnf new_cnf = c2;

    for (uint i = 0; i < c1.size(); i++) {
        bool flag = false;
        for (uint j = 0; j < c2.size(); j++) {
            if (clause_eq(c1[i], c2[j])) {
                flag = true;
            }
        }
        if (!flag) {
            new_cnf.push_back(c1[i]);
        }
    }
    return new_cnf;
}

bool Knowledge::subset(cnf c1, cnf c2) {


    for (uint i = 0; i < c1.size(); i++) {
        bool flag = false;
        for (uint j = 0; j < c2.size(); j++) {
            if (clause_eq(c1[i], c2[j])) {
                flag = true;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;

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
    func_args fa = get<1>(f);

    if (func_tok == F_VAR) {

        cout << (char) ('a' + fa[0]);

    } else if (func_tok == F_CONST) {
        vector<int> pos = bits_to_position(fa[0]);
        cout << "{";
        cout << pos[0];
        cout << ",";
        cout << pos[1];
        cout << "}";
    } else {
        string func_name = rule_parser->func_str_map[func_tok];
        cout << func_name;
        cout << "(";
        print_func_args(fa);
        cout << ")";
    }
}

void Knowledge::print_func_args(func_args fa) {

    for (uint l = 0; l < fa.size(); l++) {

        if ((fa[l] & A_CONST) > 0) {
            if ((fa[l] & A_POINT) > 0) {
                vector<int> pos = bits_to_position(fa[0]);
                cout << "{";
                cout << pos[0];
                cout << ",";
                cout << pos[1];
                cout << "}";
            } else {
                cout << fa[l];
            }

        } else {
            cout << (char) ('a' + fa[l]);
        }

        if (l != fa.size() - 1) {
            cout << ",";
        }
    }
}

func Knowledge::build_func(uint function, func_args args) {
    func return_func;
    if (function == F_VAR || function == F_CONST) {
        if (args.size() > 1) {
            cout << "WARNING: Invalid function arguments" << endl;
        }
    }
    get<0>(return_func) = function;
    get<1>(return_func) = args;
    return return_func;


}

func Knowledge::build_fvar(uint arg) {
    func return_func;
    func_args fargs;
    fargs.push_back(arg);

    get<0>(return_func) = F_VAR;
    get<1>(return_func) = fargs;
    return return_func;


}

func Knowledge::build_fconst(uint arg) {

    func return_func;
    func_args fargs;
    fargs.push_back(A_CONST | arg);

    get<0>(return_func) = F_CONST;
    get<1>(return_func) = fargs;
    return return_func;

}

pred Knowledge::build_pred(uint predicate, pred_args args) {
    pred return_pred;
    get<0>(return_pred) = predicate;
    get<1>(return_pred) = args;
    return return_pred;
}

func Knowledge::eval_func(func f) {

    func_args fargs = get<1>(f);

    if ((fargs[0] & A_CONST) > 0) { // only evaluate if there is a constant

        uint fname = get<0>(f);

        if (fname == F_NORTH) {
            fargs[0] = fargs[0] + DY;
        } else if (fname == F_SOUTH) {
            fargs[0] = fargs[0] - DY;

        } else if (fname == F_EAST) {
            fargs[0] = fargs[0] + DX;

        } else if (fname == F_WEST) {
            fargs[0] = fargs[0] + DX;

        }
        fname = F_CONST;

        return build_func(fname, fargs);

    } else {
        return f;
    }

}

uint position_to_bits(Point * position) {
    uint int_pos = position->y;
    uint x = position->x;
    int_pos = (int_pos | (x << 16)) | A_CONST | A_POINT;

    return int_pos;
}

vector<int> bits_to_position(uint bits) {
    vector<int> position;
    int x = ((bits & A_UNCONST & ~A_POINT) >> 16);
    int y = (bits & 0x0000FFFF);
    position.push_back(x);
    position.push_back(y);
    return position;
}
