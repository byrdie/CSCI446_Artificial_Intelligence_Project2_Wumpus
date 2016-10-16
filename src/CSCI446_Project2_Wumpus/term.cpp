
#include "term.h"

Term::Term() {

}

Vec::Vec() {
    pt = new Point(-100, -100);
}

Point * Vec::operator()() {
    return pt;
}

Const::Const(Point * point) {
    pt = point;
}

Point * Const::operator()() {
    return pt;
}

Var::Var() : Vec() {

}

Point * Var::operator()() {
    cout << "Illegal variable evaluation" << endl;
    return pt;
}

North::North(Vec* input){
    inp = input;
}

Point * North::operator ()(){
    
}
