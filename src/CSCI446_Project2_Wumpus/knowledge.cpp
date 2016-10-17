
#include "knowledge.h"

Knowledge::Knowledge() {

    rule_parser = new RuleParser();
    static_kb = rule_parser->parse_cnf();

}

void Knowledge::print_kb() {
    for (uint i = 0; i < static_kb.size(); i++) {
        print_clause(static_kb[i]);
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
    
    if(pred_tok & P_NEGATION){
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

    for(int l = 0; l < fa.size(); l++){
        cout << fa[l];
        if(l != fa.size() - 1){
            cout << ",";
        }
    }
    
}