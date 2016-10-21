#include "human_agent.h"
#include "engine.h"

Human_agent::Human_agent(Engine * this_engine, int sz) {

    N = sz;

    // Initialize class variables
    vector<string> rule_files;
    rule_files.push_back("Rules/all_rules.txt");
    kb = new Knowledge(sz, rule_files);
    knowledge = new World(sz, this);
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

    kb->clear_heap(x, y);
    kb->clear_stack();
    kb->add_percept_to_heap(P_AGENT, kb->position_to_bits(position), x, y);
    //add perceps to kb
    if ((next_tile & BREEZE) > 0) {
        kb->add_percept_to_heap(P_BREEZY, kb->position_to_bits(position), x, y);
    } else {
        kb->add_percept_to_heap(P_NEGATION | P_BREEZY, kb->position_to_bits(position), x, y);
    }

    if ((next_tile & STENCH) > 0) {
        kb->add_percept_to_heap(P_STINKY, kb->position_to_bits(position), x, y);
    } else {
        kb->add_percept_to_heap(P_NEGATION | P_STINKY, kb->position_to_bits(position), x, y);
    }

    /*  */
    search_tiles.clear();
    search_tiles.push_back(new Point(x, y));
    search_tiles.push_back(new Point(x + 1, y));
    search_tiles.push_back(new Point(x - 1, y));
    search_tiles.push_back(new Point(x, y + 1));
    search_tiles.push_back(new Point(x + 1, y));
    kb->heap_to_stack(search_tiles);


    //    if ((next_tile & STENCH) > 0) {
    //        add_const_clause(P_STENCH, position_to_bits(position));
    //    }

    x = position->x;
    y = position->y;

    //    infer_move(orientation);

    if (infer_pit(F_NORTH)) {
        knowledge->qt_world->set_tile(x, y + 1, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x, y + 1, POS_PIT);
    }
    if (infer_pit(F_SOUTH)) {
        knowledge->qt_world->set_tile(x, y - 1, POS_EMPTY);
    } else {
       knowledge->qt_world->set_tile(x, y - 1, POS_PIT); 
    }
    if (infer_pit(F_EAST)) {
        knowledge->qt_world->set_tile(x + 1, y, POS_EMPTY);
    }
    else {
        knowledge->qt_world->set_tile(x + 1, y, POS_PIT);
    }
    if (infer_pit(F_WEST)) {
        knowledge->qt_world->set_tile(x - 1, y, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x - 1, y, POS_PIT);
    }
    
    
    if (infer_wumpus(F_NORTH)) {
//        knowledge->qt_world->set_tile(x, y + 1, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x, y + 1, POS_WUM);
    }
    if (infer_wumpus(F_SOUTH)) {
//        knowledge->qt_world->set_tile(x, y - 1, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x, y - 1, POS_WUM);
    }
    if (infer_wumpus(F_EAST)) {
//        knowledge->qt_world->set_tile(x + 1, y, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x + 1, y, POS_WUM);
    }
    if (infer_wumpus(F_WEST)) {
//        knowledge->qt_world->set_tile(x - 1, y, POS_EMPTY);
    } else {
        knowledge->qt_world->set_tile(x - 1, y, POS_WUM);
    }
}

bool Human_agent::infer_pit(uint direction) {


    /* Build query */
    func_args fargs;
    uint position_bits = kb->position_to_bits(position);
    fargs.push_back(position_bits);
    func fquery = kb->build_func(direction, fargs);
    pred_args pquery_arg;
    pquery_arg.push_back(fquery);

    /* query for pits */
    pred p_query = kb->build_pred(P_NEGATION | P_PIT, pquery_arg);
    clause query;
    query.push_back(p_query);

#if debug_mode
    cout << "The current knowledge base is:" << endl;
    kb->print_kb(kb->kb_rules);
    kb->print_kb(kb->kb_time_stack);
    cout << endl;

    cout << "We are trying to prove:" << endl;
    kb->print_clause(query);
    cout << endl << "*************************************" << endl;
#endif
    bool result = kb->heap_input_resolution(query);
#if debug_mode
    cout << "The result is: " << result << endl;
#endif

    return result;

}

bool Human_agent::infer_wumpus(uint direction) {


    /* Build query */
    func_args fargs;
    uint position_bits = kb->position_to_bits(position);
    fargs.push_back(position_bits);
    func fquery = kb->build_func(direction, fargs);
    pred_args pquery_arg;
    pquery_arg.push_back(fquery);

    /* query for pits */
    pred p_query = kb->build_pred(P_NEGATION | P_WUMPUS, pquery_arg);
    clause query;
    query.push_back(p_query);

#if debug_mode
    cout << "The current knowledge base is:" << endl;
    kb->print_kb(kb->kb_rules);
    kb->print_kb(kb->kb_time_stack);
    cout << endl;

    cout << "We are trying to prove:" << endl;
    kb->print_clause(query);
    cout << endl << "*************************************" << endl;
#endif
    bool result = kb->heap_input_resolution(query);
#if debug_mode
    cout << "The result is: " << result << endl;
#endif

    return result;

}

void Human_agent::init_kb() {

    cnf2D * heap = kb->kb_world_heap;

    for (uint i = 0; i < (*heap).size(); i++) {
        for (uint j = 0; j < (*heap).size(); j++) {

            func_args fargs;
            uint position_bits = kb->position_to_bits(position);
            fargs.push_back(position_bits);
            func fquery = kb->build_func(F_CONST, fargs);
            pred_args pquery_arg;
            pquery_arg.push_back(fquery);
            if (i != 0 and i != N - 1) {
                if (j != 0 and j != N - 1) {

                    kb->add_percept_to_heap(P_NEGATION | P_AGENT, kb->position_to_bits(position), i, j);

                } else {
                    kb->add_percept_to_heap(P_WALL, kb->position_to_bits(position), i, j);
                }
            } else {
                kb->add_percept_to_heap(P_WALL, kb->position_to_bits(position), i, j);
            }


        }
    }

}

apoint Human_agent::find_right(Point * pos, uint dir) {
    uint x = pos->x;
    uint y = pos->y;
    switch (dir) {
        case EAST:
            y = y - 1;
            break;

        case NORTH:
            x = x + 1;
            break;

        case WEST:
            y = y + 1;
            break;

        case SOUTH:
            x = x - 1;
    }
    Point * p = new Point(x, y);
    return kb->position_to_bits(p);

}

apoint Human_agent::find_left(Point * pos, uint dir) {
    uint x = pos->x;
    uint y = pos->y;
    switch (dir) {
        case EAST:
            y = y + 1;
            break;

        case NORTH:
            x = x - 1;
            break;

        case WEST:
            y = y - 1;
            break;

        case SOUTH:
            x = x + 1;
    }
    Point * p = new Point(x, y);
    return kb->position_to_bits(p);

}

apoint Human_agent::find_forward(Point * pos, uint dir) {
    uint x = pos->x;
    uint y = pos->y;
    switch (dir) {
        case EAST:
            x = x + 1;
            break;

        case NORTH:
            y = y + 1;
            break;

        case WEST:
            x = x - 1;
            break;

        case SOUTH:
            y = y - 1;
    }
    Point * p = new Point(x, y);
    return kb->position_to_bits(p);

}

apoint Human_agent::find_backward(Point * pos, uint dir) {
    uint x = pos->x;
    uint y = pos->y;
    switch (dir) {
        case EAST:
            x = x - 1;
            break;

        case NORTH:
            y = y - 1;
            break;

        case WEST:
            x = x + 1;
            break;

        case SOUTH:
            y = y + -1;
    }
    Point * p = new Point(x, y);
    return kb->position_to_bits(p);

}

clause Human_agent::create_clause(uint predicate, vector<uint> function, vector<uint> constant) {
    pred_args pargs;
    for (uint i = 0; i < function.size(); i++) {
        func_args fargs;
        fargs.push_back(constant[i]);
        func fcon = kb->build_func(function[i], fargs);
        pargs.push_back(fcon);
    }

    pred pcon = kb->build_pred(predicate, pargs);
    clause rule;
    rule.push_back(pcon);
    return rule;
}

void Human_agent::execute_rhr() {
    vector<uint> funcs;
    funcs.push_back(F_CONST);
    funcs.push_back(F_CONST);

    //vector<uint> func_args = {kb->position_to_bits(position), (orientation | A_CONST)};

    clause t_left;
    //t_left = create_clause(P_TURNLEFT, funcs, func_args);

    clause t_right;

    //t_right = create_clause(P_TURNRIGHT, funcs, func_args);

    //clause t_forward(P_STEPFORWARD, funcs, func_args);
}
