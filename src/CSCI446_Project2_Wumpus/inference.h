
/* 
 * File:   inference.h
 * Author: byrdie
 *
 * Created on October 17, 2016, 10:04 AM
 */

#ifndef INFERENCE_H
#define INFERENCE_H

#include "knowledge.h"



class Inference {
    
    Inference();
    vector<uint> unification(pred x, pred y, vector<uint> theta);
    
    
    
    
    
};

#endif /* INFERENCE_H */

