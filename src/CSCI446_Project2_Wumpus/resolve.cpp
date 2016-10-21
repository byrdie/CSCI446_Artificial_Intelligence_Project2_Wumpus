

#include "resolve.h"

/**
 * Binary Input Resolution 2D uses two knowledge bases: static and dynamic.
 * We attempt to unify with the clauses in the dynamic knowledge base first
 * and then try the clauses in the static knowledge base. In the dynamic 
 * knowledge base clauses are stored in a 2D array corresponding to position
 * in the wumpus world. This algorithm tries only the first available 
 * resolution at each level. As such the rules have to be ordered accordingly.  
 * 
 * @param skb   static knowledge base
 * @param dkb   2D dynamic knowledge base
 * @param query  a question to be asked
 * @return true if the query is a tautology, false if the clause is
 * inconsistent with the knowledge base.
 */
bool Knowledge::binary_input_resolution_2D(cnf skb, cnf2D dkb, clause query) {

    uint max_depth = 10; // Don't keep trying after this depth

    /* Resolve clauses until we hit the max depth */
    for (uint i = 0; i < max_depth; i++) {
        
        /* Determine if there is a 2D constant (a point in the wumpus world) in our query */
        vector<apoint> coordinates = get_points_clause(query);
        
        /* Use the coordinates contained within the query check for a tautology */
        /* in the corresponding location in the 2D knowledge base */
        for(uint j = 0; j < coordinates.size(); j++){
            
            apoint bit_pt = coordinates[j];
            
        }
        

//        /* Check for tautology */
//        cnf query_cnf;
//        query_cnf.push_back(query);
//        if (subset(query_cnf, kb)) { // A tautology exists if the rule is already in the 
//            return FALSE;
//        }
        
        

    }

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

