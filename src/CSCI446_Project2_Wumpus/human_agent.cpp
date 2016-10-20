#include "human_agent.h"
#include "engine.h"

Human_agent::Human_agent(Engine * this_engine, int N) {

    // Initialize class variables
    kb = new Knowledge("../Rules/test.txt");
    knowledge = new World(N, this);
    position = new Point(START_X, START_Y - 1);
    engine = this_engine;

    my_tile = knowledge->qt_world->set_tile(position->x, position->y, AGENT);
    // ask the engine to be placed at the start position
    make_move(NORTH);


}

void Human_agent::make_move(int direction) {


    int next_tile = engine->move(direction, position);
    int x;
    int y;
    if ((next_tile & WALL) > 0) {
        add_const_clause(P_WALL, position_to_bits(position));
        vector<Point *> neighbors = knowledge->find_neighbors(position);
        x = neighbors[direction]->x;
        y = neighbors[direction]->y;
        
    } else {
        
        x = position->x;
        y = position->y;
        
    }


    if (knowledge->world_vec[x][y] == FOG) {
        knowledge->world_vec[x][y] = next_tile;
        knowledge->qt_world->set_tile(x, y, next_tile);
    }


    knowledge->qt_world->move_tile(my_tile, position->x, position->y);

    qApp->processEvents();
    qApp->processEvents();
    
    if((next_tile & WUMPUS) > 0){
        cout << "Killed by a Wumpus" << endl;
        sleep(1);
        knowledge->qt_world->view->close();
    } else if ((next_tile & PIT) > 0) {
        cout << "Fell into a pit" << endl;
        sleep(1);
        knowledge->qt_world->view->close();
    } else if ((next_tile & GOLD) > 0 ) {
        cout << "Retrived the gold" << endl;
        sleep(1);
        knowledge->qt_world->view->close();
    }

}

void Human_agent :: add_const_clause(uint predicate, uint arg){
    func_args fargs;
    fargs.push_back(arg);
    func fcon = kb->build_func(F_CONST, fargs);
    pred_args pargs;
    pargs.push_back(fcon);
    pred pcon = kb->build_pred(predicate, pargs);
    clause rule;    
    rule.push_back(pcon);
    kb->static_kb.push_back(rule);
}

uint position_to_bits(Point * position){
    uint int_pos = position->y;
    uint x = position->x;
    int_pos = (int_pos | (x << 16)) | A_CONST;
    
    return int_pos;
}