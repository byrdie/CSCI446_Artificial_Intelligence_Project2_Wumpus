
#include "term.h"

Term::Term(){
    
}

Point * Term::operator ()(){
    return new Point(0,0);
}

Const::Const(Point* val):Term(){
    value = val;
}

Point * Const::operator ()(){
    return value;
}

Var::Var():Term(){
    
}

Point * Var::operator ()(Point* pt){
    return pt;
}

North::North():Term(){
    
}

Point * North::operator ()(Point* pt){
    pt->y = pt->y + 1;
    return pt;
}

South::South():Term(){
    
}

Point * South::operator ()(Point* pt){
    pt->y = pt->y + 1;
    return pt;
}

East::East():Term(){
    
}

Point * East::operator ()(Point* pt){
    pt->x = pt->x + 1;
    return pt;
}

West::West():Term(){
    
}

Point * West::operator ()(Point* pt){
    pt->x = pt->x - 1;
    return pt;
}