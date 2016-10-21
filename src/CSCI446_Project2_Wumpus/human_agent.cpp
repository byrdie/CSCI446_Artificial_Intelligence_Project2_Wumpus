#include "human_agent.h"
#include "engine.h"

Human_agent::Human_agent(Engine * this_engine, int N) {

    // Initialize class variables
    vector<string> rule_files;
    rule_files.push_back("Rules/pit_rules.txt");
    kb = new Knowledge(N, rule_files);
    knowledge = new World(N, this);
    position = new Point(START_X, START_Y - 1);
    engine = this_engine;
    time = 0;

    orientation = SOUTH;
    my_tile = knowledge->qt_world->set_tile(position->x, position->y, AGENT);
    // ask the engine to be placed at the start position
    make_move(NORTH);


}



void Human_agent::make_move(int direction) {


    int next_tile = engine->move(direction, position);
    int x;
    int y;
    if ((next_tile & WALL) > 0) {

        vector<Point *> neighbors = knowledge->find_neighbors(position);
        x = neighbors[direction]->x;
        y = neighbors[direction]->y;
        //add wall clause to kb
        kb->add_percept_to_heap(P_WALL, kb->position_to_bits(neighbors[direction]), x, y);

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

    if ((next_tile & WUMPUS) > 0) {
        cout << "Killed by a Wumpus" << endl;
        sleep(1);
        knowledge->qt_world->view->close();
    } else if ((next_tile & PIT) > 0) {
        cout << "Fell into a pit" << endl;
        sleep(1);
        knowledge->qt_world->view->close();
    } else if ((next_tile & GOLD) > 0) {
        cout << "Retrived the gold" << endl;
        sleep(1);
        knowledge->qt_world->view->close();
    }
    //add perceps to kb
    if ((next_tile & BREEZE) > 0) {
        kb->add_percept_to_heap(P_BREEZY, kb->position_to_bits(position), x, y);
    } else {
        kb->add_percept_to_heap(P_NEGATION | P_BREEZY, kb->position_to_bits(position), x, y);
    }

//    if ((next_tile & STENCH) > 0) {
//        add_const_clause(P_STENCH, position_to_bits(position));
//    }
    
    x = position->x;
    y = position->y;

    if (infer(F_NORTH)) {
        knowledge->qt_world->set_tile(x, y + 1, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x, y + 1, POS_PIT);
    }

    if (infer(F_SOUTH)) {
        knowledge->qt_world->set_tile(x, y - 1, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x, y - 1, POS_PIT);
    }

    if (infer(F_EAST)) {
        knowledge->qt_world->set_tile(x + 1, y, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x + 1, y, POS_PIT);
    }

    if (infer(F_WEST)) {
        knowledge->qt_world->set_tile(x - 1, y, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x - 1, y, POS_PIT);
    }

    time++;     // make sure to increment the time
    
}

bool Human_agent::infer(uint direction) {

    /* Build query */
    func_args fargs;
    uint position_bits = kb->position_to_bits(position);
    fargs.push_back(position_bits);
    func fquery = kb->build_func(direction, fargs);
    pred_args pquery_arg;
    pquery_arg.push_back(fquery);
    pred p_query = kb->build_pred(P_NEGATION | P_PIT, pquery_arg);
    clause query;
    query.push_back(p_query);
#if debug_mode
    cout << "The current knowledge base is:" << endl;
    kb->print_kb(kb->kb_rules);
    cout << endl;

    cout << "We are trying to prove:" << endl;
    kb->print_clause(query);
    cout << endl << "*************************************" << endl;
#endif
//    cnf neg_query = kb->negate_clause(query);
    bool result = kb->heap_input_resolution(query, position->x, position->y);
#if debug_mode
    cout << "The result is: " << result << endl;
#endif
    return result;

}

apoint Human_agent::find_right(Point * pos, uint dir){
    uint x = pos->x;
    uint y = pos->y;
    switch (dir){
        case EAST:
            y = y -1;
            break;
            
        case NORTH:
            x = x +1;
            break;
            
        case WEST:
            y = y + 1;
            break;
            
        case SOUTH:
            x = x -1;
    }
    Point * p = new Point(x,y);
    return kb->position_to_bits(p);
    
}

apoint Human_agent::find_left(Point * pos, uint dir){
    uint x = pos->x;
    uint y = pos->y;
    switch (dir){
        case EAST:
            y = y + 1;
            break;
            
        case NORTH:
            x = x - 1;
            break;
            
        case WEST:
            y = y-1;
            break;
            
        case SOUTH:
            x =x + 1;
    }
    Point * p = new Point(x,y);
    return kb->position_to_bits(p);
    
}

apoint Human_agent::find_forward(Point * pos, uint dir){
    uint x = pos->x;
    uint y = pos->y;
    switch (dir){
        case EAST:
            x = x + 1;
            break;
            
        case NORTH:
            y = y+1;
            break;
            
        case WEST:
            x = x-1;
            break;
            
        case SOUTH:
            y = y -1;
    }
    Point * p = new Point(x,y);
    return kb->position_to_bits(p);
    
}

