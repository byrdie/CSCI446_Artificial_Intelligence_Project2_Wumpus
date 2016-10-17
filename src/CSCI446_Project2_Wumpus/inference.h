
/* 
 * File:   inference.h
 * Author: byrdie
 *
 * Created on October 17, 2016, 10:04 AM
 */

#ifndef INFERENCE_H
#define INFERENCE_H


using namespace std;


class Inference {
    
    Inference();
    vector<int> unification();
    bool resolution(cnf kb, clause query);
    cnf resolve(clause c_i, clause c_j);
    
    
};

#endif /* INFERENCE_H */

