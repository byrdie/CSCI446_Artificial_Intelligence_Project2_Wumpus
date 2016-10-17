
/* 
 * File:   inference.h
 * Author: byrdie
 *
 * Created on October 17, 2016, 10:04 AM
 */

#ifndef INFERENCE_H
#define INFERENCE_H

#include "knowledge.h"

using namespace std;

class Inference {
    
    Inference();
    vector<uint> unification(pred x, pred y, vector<uint> theta);
    bool resolution(cnf kb, clause query);
    cnf resolve(clause c_i, clause c_j);
    
    
};

#endif /* INFERENCE_H */

