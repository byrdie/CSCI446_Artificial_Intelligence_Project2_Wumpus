
#include "predicate.h"

Predicate::Predicate(bool neg){  
    negation = neg;    
}

bool Predicate::operator ()(){
    cout << "operation on empty predicate" << endl;
    return false;
}

Breezy::Breezy(bool neg, Term inp):Predicate(neg){
    
}

bool Breezy::operator ()(){
    return true;
}