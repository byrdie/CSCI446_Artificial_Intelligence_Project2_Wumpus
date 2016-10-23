

#include "resolve.h"

uint Knowledge::input_resolution_bfs(clause query) {

    cnf kb = kb_time_stack; // Make a copy of the KB

    /* negate theorem to be proven */
    query = negate_clause(query)[0];

    //    /* Check if the rule is a tautology */
    //    cnf query_cnf;
    //    query_cnf.push_back(resolvents[l]);
    //    if (subset(query_cnf, kb)) { // A tautology exists if the rule is already in the KB
    //#if debug_mode
    //        cout << setw((i + 1) * 5) << ' ';
    //        cout << "The rule ";
    //        print_clause(input);
    //        cout << " is a tautology.";
    //        cout << endl;
    //#endif
    //        return FALSE;
    //    }

    /* Define a tree to store the results of the bfs */
    uint max_depth = 12; // Don't keep trying after this depth
    vector<vector < clause >> rtree(max_depth);

    /* Define the query to be at the root node */
    vector<clause> rtree_top;
    rtree_top.push_back(query);
    rtree[0] = rtree_top;

    /* Loop through each layer of the resolution tree */
    for (uint i = 0; i < rtree.size() - 1; i++) {

        /* loop through though each resolvent for each layer */
        vector<clause> this_row = rtree[i];
        vector<clause> next_row;
        for (uint j = 0; j < this_row.size(); j++) {

            /* Select the next rule to be resolved */
            clause input = this_row[j];
//            clause input = eval_clause(this_row[j]);



            /* Attempt to resolve the input with every clause in the KB */
            for (uint k = 0; k < kb.size(); k++) {

//#if debug_mode
//                cout << setw(i * 5) << ' ';
//                cout << "Resolve ";
//                print_clause(input);
//                cout << " and ";
//                print_clause(kb[k]);
//                cout << endl;
//#endif

                /* Possibly delete rules as they're used here */


                /* Attempt to resolve each clause */
                cnf resolvents = resolve(kb[k], input);

                /* Loop over the resolvents and check for an inconsistency
                 * If there is no inconsistency, set the clause variable
                 * equal to the resolvent and restart the main loop */
                for (uint l = 0; l < resolvents.size(); l++) {

#if debug_mode
                    cout << setw(i * 5) << ' ';
                    cout << "Resolve ";
                    print_clause(input);
                    cout << " and ";
                    print_clause(kb[k]);
                    cout << endl;
#endif

                    /* Check if the rule is a tautology */
                    cnf query_cnf;
                    query_cnf.push_back(resolvents[l]);
                    if (subset(query_cnf, kb)) { // A tautology exists if the rule is already in the KB
#if debug_mode
                        cout << setw((i + 1) * 5) << ' ';
                        cout << "The rule ";
                        print_clause(resolvents[l]);
                        cout << " is a tautology.";
                        cout << endl;
#endif
                        return FALSE;
                    }

                    /* Inconsistency check. If two clauses resolve to an empty
                     * clause the two clauses are inconsistent */
                    if (resolvents[l].empty()) {
#if debug_mode
                        cout << setw((i + 1) * 5) << ' ';
                        cout << "The rule ";
                        print_clause(input);
                        cout << " is a contradiction.";
                        cout << endl;
#endif
                        return TRUE;
                    }

#if debug_mode
                    cout << setw((i + 1) * 5) << ' ';
                    cout << "Result ";
                    print_clause(resolvents[l]);
                    cout << endl;
#endif

                    /* If the resolvent is consistent, restart the main loop
                     * with the query as the resolvent*/
                    next_row.push_back(resolvents[l]);

                }



            }

        }
        rtree[i + 1] = next_row;
    }

    return NOT_FOUND;
}

bool Knowledge::heap_input_resolution(clause query) {

    cnf rkb = kb_rules; // Make a copy of the rules
    cnf pt_kb = kb_time_stack; // Make a copy of the heap

    /* negate theorem to be proven */
    query = negate_clause(query)[0];



    clause input_query = query; // Make a copy of the input query for later



    /* Resolve clauses until we hit the max depth */
    uint max_depth = 10; // Don't keep trying after this depth
    for (uint i = 0; i < max_depth; i++) {

        query = eval_clause(query); // Evaluate all the functions within the query to prevent function nesting

        /* Check if the query is a tautology */
        cnf query_cnf;
        query_cnf.push_back(query);
        if (subset(query_cnf, pt_kb)) { // A tautology exists if the rule is already in th
            return FALSE;
        }

        for (int k = pt_kb.size() - 1; k > -1; k--) { // loop over clauses in inverse order

#if debug_mode
            cout << setw(i * 5) << ' ';
            cout << "Resolve ";
            print_clause(query);
            cout << " and ";
            print_clause(pt_kb[k]);
            cout << endl;
#endif

            /* Possibly delete rules as they're used here */

            /* Attempt to resolve each clause */
            cnf resolvents = resolve(pt_kb[k], query);

            /* Loop over the resolvents and check for an inconsistency
             * If there is no inconsistency, set the clause variable
             * equal to the resolvent and restart the main loop */
            for (uint l = 0; l < resolvents.size(); l++) {

                /* Inconsistency check. If two clauses resolve to an empty
                 * clause the two clauses are inconsistent */
                if (resolvents[l].empty()) {
                    return TRUE;
                }

                /* If the resolvent is consistent, restart the main loop
                 * with the query as the resolvent*/
                query = resolvents[l];
                goto MAIN_LOOP_EXIT;

            }
        }

        //        /* Loop over the clauses in the static rules */
        //        for (uint k = 0; k < kb_rules.size(); k++) { // loop over clauses
        //#if debug_mode
        //            cout << setw(i * 5) << ' ';
        //            cout << "Resolve ";
        //            print_clause(query);
        //            cout << " and ";
        //            print_clause(kb_rules[k]);
        //            cout << endl;
        //#endif
        //            
        //            /* Attempt to resolve each clause */
        //            cnf resolvents = resolve(kb_rules[k], query);
        //
        //            /* Loop over the resolvents and check for an inconsistency
        //             * If there is no inconsistency, set the clause variable
        //             * equal to the resolvent and restart the main loop */
        //            for (uint l = 0; l < resolvents.size(); l++) {
        //
        //                /* Inconsistency check. If two clauses resolve to an empty
        //                 * clause the two clauses are inconsistent */
        //                if (resolvents[l].empty()) {
        //                    return TRUE;
        //                }
        //
        //                /* If the resolvent is consistent, restart the main loop
        //                 * with the query as the resolvent*/
        //                query = resolvents[l];
        //                goto MAIN_LOOP_EXIT;
        //
        //            }
        //        }


MAIN_LOOP_EXIT: // Goto statement used to break out of triple loop
        continue;
    }
    return NOT_FOUND;
}

/**
 * Recursive function to execute linear resolution strategy
 * @param kb
 * @param query MUST BE ALREADY NEGATED!
 * @return 0 for false, 1 for true, 2 for not found 
 */
uint Knowledge::linear_resolution(cnf kb, clause query, uint indent) {

    if (indent > 30) {
        cout << "RECURSION LIMIT REACHED!" << endl;
        return FALSE;
    }



    /* Check for tautology */
    cnf query_cnf;
    query_cnf.push_back(query);
    if (subset(query_cnf, kb)) { // A tautology exists if the rule is already in the 
        return FALSE;
    }

    /* Loop through the knowledge base to find a resolution */
    for (uint i = 0; i < kb.size(); i++) {

        /* After we use a rule, move to the back of the rule priority */
        cnf kbc = kb;
        auto it = kbc.begin() + i;
        rotate(it, it + 1, kbc.end());

        /* Attempt to resolve each clause */
        cnf resolvents = resolve(kb[i], query);

#if debug_mode
        cout << setw(indent) << ' ';
        cout << "Resolve ";
        print_clause(query);
        cout << " and ";
        print_clause(kb[i]);
        cout << endl;
#endif

        /* Loop through the possible resolvents and recursively apply linear resolution to each*/
        for (uint j = 0; j < resolvents.size(); j++) {

            /* Check for an inconsistency */
            if (resolvents[j].empty()) {
                return TRUE;
            }

            /* Apply linear resolution to the resolvents */
            uint result = linear_resolution(kbc, resolvents[j], indent + 5);

            /* return if linear_resolution found a result, otherwise continue looping */
            if (result != NOT_FOUND) {
                return result;
            }

        }


    }
    return NOT_FOUND;
}

/**
 * Resolve returns the set of all possible clauses obtained by resolving the
 * two inputs ci and cy
 * @param ci
 * @param cj
 * @return a set of resolved clauses
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

                /* Remove negation so that the predicates may be unified */
                get<0>(pi) = get<0>(pi) & P_UNNEGATION;
                get<0>(pj) = get<0>(pj) & P_UNNEGATION;

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

                    /* Apply the list of substitutions */
                    for (uint k = 0; k < sub_list.size(); k++) {

                        ci_copy = apply_sub_to_clause(ci_copy, sub_list[k]);
                        cj_copy = apply_sub_to_clause(cj_copy, sub_list[k]);

                    }

                    /* A resolvent is a union of the clauses after resolution */
                    clause union_c = concat_clause(ci_copy, cj_copy);



                    /* Add the new resolvent to the list of resolvents */
                    resolvents.push_back(union_c);
                }
            }

        }
    }
    return resolvents;
}

bool Knowledge::is_neg(pred p) {
    if ((get<0>(p) & P_NEGATION) > 0) {
        return true;
    } else {
        return false;
    }
}

