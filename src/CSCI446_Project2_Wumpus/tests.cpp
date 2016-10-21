
#include "tests.h"

//void test_unification() {
//    Knowledge * kb = new Knowledge("../Rules/unificiation_test.txt");
//
//    for (uint i = 0; i < kb->static_kb.size() / 2; i++) {
//        pred p1 = kb->static_kb[2 * i][0];
//        pred p2 = kb->static_kb[2 * i + 1][0];
//
//
//
//        kb->print_pred(p1);
//        cout << endl;
//        kb->print_pred(p2);
//        cout << endl;
//        cout << endl;
//        theta sub_list;
//        sub_list = kb->unification(p1, p2, sub_list);
//
//        cout << "num subs: " << sub_list.size() << endl;
//
//        for (uint j = 0; j < sub_list.size(); j++) {
//            kb->print_pred_args(sub_list[j]);
//            cout << endl;
//
//            p1 = kb->apply_sub_to_pred(p1, sub_list[j]);
//            p2 = kb->apply_sub_to_pred(p2, sub_list[j]);
//
//        }
//        cout << endl;
//        kb->print_pred(p1);
//        cout << endl;
//        kb->print_pred(p2);
//        cout << endl;
//        cout << "----------------------" << endl;
//    }
//}
//
//void test_resolve() {
//
//    Knowledge * kb = new Knowledge("../Rules/test.txt");
//
//    for (uint i = 0; i < kb->static_kb.size(); i++) {
//        for (uint j = 0; j < kb->static_kb.size(); j++) {
//
//            if (i != j) {
//                clause c1 = kb->static_kb[i];
//                clause c2 = kb->static_kb[j];
//
//                cout << "Input Clauses" << endl;
//                kb->print_clause(c1);
//                cout << endl;
//                kb->print_clause(c2);
//                cout << endl;
//
//
//                cnf resolvents = kb->resolve(c1, c2);
//
//                cout << endl << "Resolved Clauses:" << endl;
//                kb->print_kb(resolvents);
//
//                cout << "----------------------" << endl;
//            }
//
//        }
//    }
//}
//
//
//void test_linear_resolution() {
//    Knowledge * kb = new Knowledge("../Rules/test.txt");
//
//    /* Add Breezy(A) to the knowledge base */
//    uint con = 127 | A_CONST;
//    func_args fargs;
//    fargs.push_back(con);
//    func fcon = kb->build_func(F_CONST, fargs);
//    pred_args pargs;
//    pargs.push_back(fcon);
//    pred pcon = kb->build_pred(P_NEGATION | P_BREEZY, pargs);
//    clause rule;    
//    rule.push_back(pcon);
//    kb->static_kb.insert(kb->static_kb.begin(), rule);
//
//    /* Build query */
//    func fquery = kb->build_func(F_NORTH, fargs);
//    pred_args pquery_arg;
//    pquery_arg.push_back(fquery);
//    pred p_query = kb->build_pred(P_NEGATION | P_PIT, pquery_arg);
//    clause query;
//    query.push_back(p_query);
//
//    cout << "The current knowledge base is:" << endl;
//    kb->print_kb(kb->static_kb);
//    cout << endl;
//
//    cout << "We are trying to prove:" << endl ;
//    kb->print_clause(query);
//    cout << endl << "*************************************" << endl;
//
//    cnf neg_query = kb->negate_clause(query);
//    uint result = kb->linear_resolution(kb->static_kb, neg_query[0],0);
//
//    cout << "The result is: " << result << endl;
//
//}
