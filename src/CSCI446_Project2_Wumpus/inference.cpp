/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "inference.h"
Inference :: Inference(){
    
}

vector<uint> Inference :: unification(pred x, pred y, vector<uint> theta){
    //Check that the same predicates are used and the same number of arguments are used.
    if ((get<0>(x) != get<0>(y)) || (get<1>(x).size() != get<1>(y).size()) ){
        return theta;
    }
    for(int i = 0; i< get<1>(x).size(); i++){
        if((get<0>(get<1>(x)[i]) != get<0>(get<1>(y)[i]))){
            return theta;
        }
    }
}