/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "inference.h"

Inference::Inference() {

}

vector<uint> Inference::unification(pred x, pred y, vector<uint> theta) {
    //Check that the same predicates are used and the same number of arguments are used.
    if ((get<0>(x) != get<0>(y)) || (get<1>(x).size() != get<1>(y).size())) {
        return theta;
    }
    for (int i = 0; i < get<1>(x).size(); i++) {
        if ((get<0>(get<1>(x)[i]) != get<0>(get<1>(y)[i]))) {
            return theta;
        }
    }
}

cnf Inference::resolve(Knowledge * kb, clause c_i, clause c_j) {

    cnf resolvents;     // Allocate space for the new formulae
    
    /* Loop through every literal in both clauses */
    for (int i = 0; i < c_i.size(); i++) {
        for (int j = 0; j < c_j.size(); j++) {

            pred next_pi = c_i[i];
            pred next_pj = c_j[j];

            /* Check that one (not both) of the objects are negated */
            if (kb->is_neg(next_pi) xor kb->is_neg(next_pj)) {
                vector<uint> sub;
                sub = unification(next_pi, next_pj, sub);
                
                /* Check if the unification process succeeded before continuing */
                if(!sub.empty()){
                    
                }
            }

        }
    }

}