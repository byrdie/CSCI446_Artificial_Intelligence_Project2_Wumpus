

#include "resolve.h"

uint Knowledge::input_resolution_bfs(clause query) {



    cnf kb = kb_time_stack; // Make a copy of the KB

    /* negate theorem to be proven */
    query = negate_clause(query)[0];

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
            //                        clause input = eval_clause(this_row[j]);


            /* Attempt to resolve the input with every clause in the KB */
            for (uint k = 0; k < kb.size(); k++) {

                /* Possibly delete rules as they're used here */


                /* Attempt to resolve each clause */
                cnf resolvents = resolve(kb[k], input);

                /* Loop over the resolvents and check for an inconsistency
                 * If there is no inconsistency, set the clause variable
                 * equal to the resolvent and restart the main loop */
                for (uint l = 0; l < resolvents.size(); l++) {

                    print_resolution(input, kb[k], i);


                    /* Check if the rule is a tautology */
                    cnf query_cnf;
                    query_cnf.push_back(resolvents[l]);
                    if (subset(query_cnf, kb)) { // A tautology exists if the rule is already in the KB                   
                        print_tautology(resolvents[l], i);
                        return FALSE;
                    }

                    /* Inconsistency check. If two clauses resolve to an empty
                     * clause the two clauses are inconsistent */
                    if (resolvents[l].empty()) {
                        print_contradiction(input, i);
                        return TRUE;
                    }

                    print_result(resolvents[l], i);


                    /* If the resolvent is consistent, restart the main loop
                     * with the query as the resolvent*/
                    next_row.push_back(resolvents[l]);

                }



            }

            /* Usually not necessary to check more than this */
            if (j == 1) {
                break;
            }

        }
        rtree[i + 1] = next_row;
    }

    return NOT_FOUND;
}

void Knowledge::print_tautology(clause c, uint i) {
#if debug_mode
    out << setw(i * 1) << '-';
    out << "The rule ";
    print_clause(&out, c);
    out << " is a tautology.";
    out << endl;

    latex << "\\texttt{";
    latex << setw(i * 1) << '-';
    latex << "The rule ";
    print_clause(&latex, c);
    latex << " is a tautology.";
    latex << "} \\\\";
    latex << endl;
#endif
}

void Knowledge::print_contradiction(clause c, uint i) {
#if debug_mode
    
    out << setw((i + 1) * 5) << '-';
    out << "The rule ";
    print_clause(&out, c);
    out << " is a contradiction.";
    out << endl;

    latex << "\\texttt{";
    latex << setw((i + 1) * 5) << '-';
    latex << "The rule ";
    print_clause(&latex, c);
    latex << " is a contradiction.";
    latex << "} \\\\";
    latex << endl;
#endif
}

void Knowledge::print_resolution(clause c1, clause c2, uint i) {
#if debug_mode
    out << setfill('-') << setw((i + 1) * 5);
    out << "Resolve ";
    print_clause(&out, c1);
    out << " and ";
    print_clause(&out, c2);
    out << endl;

    latex << setfill('-');
    latex << "\\texttt{";
    latex << setw(i * 5) << '-';
    latex << "Resolve ";
    print_clause(&latex, c1);
    latex << " and ";
    print_clause(&latex, c2);
    latex << "}\\\\";
    latex << endl;
#endif
}

void Knowledge::print_result(clause c, uint i) {
#if debug_mode
    out << setw((i + 1) * 5) << '-';
    out << "Result ";
    print_clause(&out, c);
    out << endl;

    latex << "\\texttt{";
    latex << setw((i + 1) * 5) << '-';
    latex << "Result ";
    print_clause(&latex, c);
    latex << "}\\\\";
    latex << endl;
#endif
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

