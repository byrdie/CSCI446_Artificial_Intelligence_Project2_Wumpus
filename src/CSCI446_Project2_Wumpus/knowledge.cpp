
#include "knowledge.h"
#include <typeinfo>

Knowledge::Knowledge(uint sz, vector<string> rule_files) {

    N = sz;
    out.open("../output/output.txt");
    latex.open("../output/latex_output.tex");
    rule_parser = new RuleParser();

    kb_rules = rule_parser->parse_cnf(rule_files[0]);
    for (uint i = 1; i < rule_files.size(); i++) {
        kb_rules = rule_parser->parse_cnf(rule_files[i]);
    }

    kb_world_heap = new cnf2D(N + 2, vector<cnf>(N + 2));
    for (uint i = 0; i < (*kb_world_heap).size(); i++) {
        for (uint j = 0; j < (*kb_world_heap)[0].size(); j++) {
            Point pt(i, j);
            //            add_percept_to_heap(P_NEGATION | P_AGENT, build_fcardinal(EAST, i - 1, j), i, j);
            //            add_percept_to_heap(P_NEGATION | P_AGENT, build_fcardinal(WEST, i + 1, j), i, j);
            //            add_percept_to_heap(P_NEGATION | P_AGENT, build_fcardinal(NORTH, i, j - 1), i, j);
            //            add_percept_to_heap(P_NEGATION | P_AGENT, build_fcardinalSOUTH, i, j + 1), i, j);

            add_percept_to_heap(P_NEGATION | P_WALL, build_fcardinal(EAST, i - 1, j), i, j);
            add_percept_to_heap(P_NEGATION | P_WALL, build_fcardinal(WEST, i + 1, j), i, j);
            add_percept_to_heap(P_NEGATION | P_WALL, build_fcardinal(NORTH, i, j - 1), i, j);
            add_percept_to_heap(P_NEGATION | P_WALL, build_fcardinal(SOUTH, i, j + 1), i, j);

            //            add_percept_to_heap(P_NEGATION | P_WALL, build_fcardinal(SOUTH, i, j), i, j);
            //            add_percept_to_heap(P_NEGATION | P_WALL, build_fcardinal(EAST, i, j), i, j);
            //            add_percept_to_heap(P_NEGATION | P_WALL, build_fcardinal(WEST, i, j), i, j);
        }
    }



    func_inv[F_CONST] = F_CONST;
    func_inv[F_VAR] = F_VAR;
    func_inv[F_NORTH] = F_SOUTH;
    func_inv[F_SOUTH] = F_NORTH;
    func_inv[F_EAST] = F_WEST;
    func_inv[F_WEST] = F_EAST;
    func_inv[F_FORWARD] = F_BACKWARD;
    func_inv[F_RIGHT] = F_LEFT;
    func_inv[F_LEFT] = F_RIGHT;
    func_inv[F_BACKWARD] = F_FORWARD;
    func_inv[F_GETX] = F_GETX;
    func_inv[F_GETY] = F_GETY;

}

void Knowledge::clear_stack() {
    kb_time_stack.clear();
}

void Knowledge::clear_heap(uint x, uint y) {
    ((*kb_world_heap)[x][y]).clear();
}

void Knowledge::add_to_rules(pred_name pname, func_arg parg) {

    func_args fargs;
    fargs.push_back(parg);
    func fcon = build_func(F_CONST, fargs);
    pred_args pargs;
    pargs.push_back(fcon);
    pred pcon = build_pred(pname, pargs);
    clause rule;
    rule.push_back(pcon);

    kb_rules.push_back(rule);

}

void Knowledge::add_percept_to_heap(pred_name pname, func_arg parg, uint x, uint y) {

    func_args fargs;
    fargs.push_back(parg);
    func fcon = build_func(F_CONST, fargs);
    pred_args pargs;
    pargs.push_back(fcon);
    pred pcon = build_pred(pname, pargs);
    clause rule;
    rule.push_back(pcon);

    cnf pt_kb = (*kb_world_heap)[x][y];

    for (uint i = 0; i < pt_kb.size(); i++) {
        if (clause_eq(rule, pt_kb[i])) {
            return;
        }
    }
    pt_kb.push_back(rule);
    (*kb_world_heap)[x][y] = pt_kb;

}

void Knowledge::add_percept_to_heap(pred_name pname, pred_arg parg, uint x, uint y) {

    pred_args pargs;
    pargs.push_back(parg);
    pred pcon = build_pred(pname, pargs);
    clause rule;
    rule.push_back(pcon);

    cnf pt_kb = (*kb_world_heap)[x][y];

    for (uint i = 0; i < pt_kb.size(); i++) {
        if (clause_eq(rule, pt_kb[i])) {
            return;
        }
    }
    pt_kb.push_back(rule);
    (*kb_world_heap)[x][y] = pt_kb;

}

void Knowledge::heap_to_stack(vector<Point *> pts) {

    /* Make sure the stack is clear */
    clear_stack();

    for (uint i = 0; i < (*kb_world_heap).size(); i++) {
        for (uint j = 0; j < (*kb_world_heap)[i].size(); j++) {
            for (uint k = 0; k < (*kb_world_heap)[i][j].size(); k++) {
                kb_time_stack.push_back((*kb_world_heap)[i][j][k]);
            }
        }
    }

    //    /* add information from heap */
    //    for (uint i = 0; i < pts.size(); i++) {
    //
    //        uint x = pts[i]->x;
    //        uint y = pts[i]->y;
    //
    //        cnf kb_pt = (*kb_world_heap)[x][y];
    //        for (uint j = 0; j < kb_pt.size(); j++) {
    //
    //            kb_time_stack.push_back(kb_pt[j]);
    //
    //        }
    //
    //    }

    /* add rules */
    for (uint i = 0; i < kb_rules.size(); i++) {
        kb_time_stack.push_back(kb_rules[i]);
    }





}

void Knowledge::add_percept_to_stack(pred_name pname, func_arg parg) {

    func_args fargs;
    fargs.push_back(parg);
    func fcon = build_func(F_CONST, fargs);
    pred_args pargs;
    pargs.push_back(fcon);
    pred pcon = build_pred(pname, pargs);
    clause rule;
    rule.push_back(pcon);


    for (uint i = 0; i < kb_time_stack.size(); i++) {
        if (clause_eq(rule, kb_time_stack[i])) {
            return;
        }
    }
    kb_time_stack.push_back(rule);

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
 *  This function set will return a list of all the constants found within
 * @param c     a clause in cnf
 * @return a    vector of constants in logic form
 */
vector<uint> Knowledge::get_points_clause(clause c) {

    vector<uint> constants;

    for (uint j = 0; j < c.size(); j++) {

        vector<uint> lower_constants = get_points_pred_args(get<1>(c[j]));

        for (uint k = 0; k < lower_constants.size(); k++) {
            constants.push_back(lower_constants[k]);
        }

    }

    return constants;

}

vector<aconst> Knowledge::get_points_pred(pred p) {

    return get_points_pred_args(p_args(p));

}

vector<aconst> Knowledge::get_points_pred_args(pred_args pa) {

    vector<aconst> constants;

    for (uint k = 0; k < pa.size(); k++) {
        vector<aconst> lower_constants = get_points_func(pa[k]);

        for (uint l = 0; l < lower_constants.size(); l++) {
            constants.push_back(lower_constants[l]);
        }

    }

    return constants;

}

vector<aconst> Knowledge::get_points_func(func f) {

    return get_points_func_args(f_args(f));

}

vector<aconst> Knowledge::get_points_func_args(func_args fa) {

    vector<uint> constants;

    for (uint l = 0; l < fa.size(); l++) {

        if ((fa[l] & A_POINT) > 0) {
            constants.push_back(fa[l]);
        }
    }

    return constants;

}

/**
 * Series of function to print out a knowledge base for viewing
 * @param kb the knowledge base in CNF form
 */
void Knowledge::print_kb(ofstream *s, cnf kb) {
    for (uint i = 0; i < kb.size(); i++) {
        print_clause(s, kb[i]);
        *s << endl;
    }
}

void Knowledge::print_clause(ofstream *s, clause c) {
    for (uint j = 0; j < c.size(); j++) {
        print_pred(s, c[j]);
        if (j != (c.size() - 1)) {
            *s << " || ";
        }
    }
}

void Knowledge::print_pred(ofstream *s, pred p) {

    int pred_tok = get<0>(p);

    if (pred_tok & P_NEGATION) {
        *s << "!";
        pred_tok = pred_tok & P_UNNEGATION;
    }

    string pred_name = rule_parser->pred_str_map[pred_tok];
    *s << pred_name;
    *s << "(";
    print_pred_args(s, get<1>(p));
    *s << ")";
}

void Knowledge::print_pred_args(ofstream *s, pred_args pa) {

    for (uint k = 0; k < pa.size(); k++) {
        print_func(s, pa[k]);
        if (k != (pa.size() - 1)) {
            *s << ", ";
        }
    }
}

void Knowledge::print_func(ofstream *s, func f) {
    int func_tok = get<0>(f);
    func_args fa = get<1>(f);

    if (func_tok == F_VAR) {

        *s << (char) ('a' + fa[0]);

    } else if (func_tok == F_CONST) {
        Point pos = bits_to_position(fa[0]);
        *s << "{";
        *s << pos.x;
        *s << ",";
        *s << pos.y;
        *s << "}";
    } else {
        string func_name = rule_parser->func_str_map[func_tok];
        *s << func_name;
        *s << "(";
        print_func_args(s, fa);
        *s << ")";
    }
}

void Knowledge::print_func_args(ofstream *s, func_args fa) {

    for (uint l = 0; l < fa.size(); l++) {

        if ((fa[l] & A_CONST) > 0) {
            if ((fa[l] & A_POINT) > 0) {
                Point pos = bits_to_position(fa[0]);
                *s << "{";
                *s << pos.x;
                *s << ",";
                *s << pos.y;
                *s << "}";
            } else {
                *s << fa[l];
            }

        } else {
            *s << (char) ('a' + (fa[l] % 26));
        }

        if (l != fa.size() - 1) {
            *s << ",";
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

func Knowledge::build_fcardinal(uint dir, uint x, uint y) {

    func_name fname;

    switch (dir) {
        case EAST:
            fname = F_EAST;
            break;
        case NORTH:
            fname = F_NORTH;
            break;
        case WEST:
            fname = F_WEST;
            break;
        case SOUTH:
            fname = F_SOUTH;
            break;
    }

    Point pt(x, y);
    apoint bpt = position_to_bits(&pt);
    func_args fargs;
    fargs.push_back(bpt);
    return build_func(fname, fargs);

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

clause Knowledge::eval_clause(clause c) {

    clause c_eval;

    for (uint i = 0; i < c.size(); i++) {

        c_eval.push_back(eval_pred(c[i]));

    }

    return c_eval;

}

pred Knowledge::eval_pred(pred p) {

    get<1>(p) = eval_pred_args(p_args(p));

    return p;

}

pred_args Knowledge::eval_pred_args(pred_args pa) {

    pred_args pa_eval;

    for (uint i = 0; i < pa.size(); i++) {

        pa_eval.push_back(eval_func(pa[i]));

    }

    return pa_eval;

}

func Knowledge::eval_func(func f) {

    func_args fargs = get<1>(f);

    /* Only evaluate if all arguments are constants */
    bool flag = false;
    for (uint i = 0; i < fargs.size(); i++) {
        if ((fargs[i] & A_CONST) == 0) {
            flag = true;
        }
    }
    if (flag) {
        return f;
    }



    uint fname = get<0>(f);

    if (fargs.size() == 1) {
        if (fname == F_NORTH) {
            fargs[0] = fargs[0] + DY;
        } else if (fname == F_SOUTH) {
            fargs[0] = fargs[0] - DY;
        } else if (fname == F_EAST) {
            fargs[0] = fargs[0] + DX;
        } else if (fname == F_WEST) {
            fargs[0] = fargs[0] - DX;
        } else if (fname == F_GETX) {
            fargs[0] = ((fargs[0] & ONLYX) >> 16) | A_CONST;
        } else if (fname == F_GETY) {
            fargs[0] = (fargs[0] & ONLYY) | A_CONST;
        }
    } else if (fargs.size() == 2) {

        if (fname == F_FORWARD or fname == F_BACKWARD or fname == F_RIGHT or fname == F_LEFT) {

            if (fargs[1] == NORTH) {
                fargs[0] = fargs[0] + DY;
            } else if (fargs[1] == SOUTH) {
                fargs[0] = fargs[0] - DY;
            } else if (fargs[1] == EAST) {
                fargs[0] = fargs[0] + DX;
            } else if (fargs[1] == WEST) {
                fargs[0] = fargs[0] - DX;
            }

        }

    }


    fname = F_CONST;

    return build_func(fname, fargs);



}

apoint Knowledge::position_to_bits(Point * position) {
    uint int_pos = position->y;
    uint x = position->x;
    int_pos = (int_pos | (x << 16)) | A_CONST | A_POINT;

    return int_pos;
}

Point Knowledge::bits_to_position(apoint bits) {
    int x = ((bits & ~A_CONST & ~A_POINT) >> 16);
    int y = (bits & 0x0000FFFF);
    Point position(x, y);
    return position;
}

pred_name Knowledge::p_name(pred p) {
    return get<0>(p);
}

pred_args Knowledge::p_args(pred p) {

    return get<1>(p);
}

pred_arg Knowledge::p_argi(pred p, uint index) {

    return (p_args(p))[index];

}

func_name Knowledge::f_name(func f) {
    return get<0>(f);
}

func_args Knowledge::f_args(func f) {
    return get<1>(f);
}

func_arg Knowledge::f_argi(func f, uint index) {
    return (f_args(f))[index];
}

