
#include "knowledge.h"

Knowledge::Knowledge() {



}

void initialize_token_map() {
    pred_tok_map["Breezy"] = P_BREEZY;
    pred_tok_map["Pit"] = P_PIT;
    pred_tok_map["Safe"] = P_SAFE;


    func_tok_map["North"] = F_NORTH;
    func_tok_map["South"] = F_SOUTH;
    func_tok_map["East"] = F_EAST;
    func_tok_map["West"] = F_WEST;
   
}