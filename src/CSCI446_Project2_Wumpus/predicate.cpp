
#include "predicate.h"

Predicate::Predicate(bool neg){  
    negation = neg;    
}

bool Predicate::operator ()(){
    cout << "operation on empty predicate" << endl;
    return false;
}

Breezy::Breezy(bool neg, Term * inp1):Predicate(neg){
    arg1 = inp1;
}

bool Breezy::operator ()(){
    return true;
}