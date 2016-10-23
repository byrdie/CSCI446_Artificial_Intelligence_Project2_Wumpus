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

    orientation = NORTH;
    my_tile = knowledge->qt_world->set_tile(position->x, position->y, AGENT);
    // ask the engine to be placed at the start position
    make_move(NORTH);

    kb->print_kb(kb->kb_rules);



}

void Human_agent::make_move(int direction) {



    int next_tile = engine->move(direction, position);
    int x;
    int y;
    neighbors = knowledge->find_neighbors(position);
    if ((next_tile & WALL) > 0) {


        x = neighbors[direction]->x;
        y = neighbors[direction]->y;

        //        kb->clear_heap(x, y);
        kb->clear_stack();

        //add wall clause to kb
        kb->add_percept_to_heap(P_WALL, kb->build_fcardinal(direction, position->x, position->y), x, y);

    } else {

        x = position->x;
        y = position->y;

        kb->clear_heap(x, y);
        kb->clear_stack();

        kb->add_percept_to_heap(P_NEGATION | P_WALL, kb->position_to_bits(position), x, y);



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
    } else {

    }

    if ((next_tile & PIT) > 0) {
        cout << "Fell into a pit" << endl;
        sleep(1);
        knowledge->qt_world->view->close();
    } else {
    }
    if ((next_tile & GOLD) > 0) {
        engine->score = engine->score + 1000;
        cout << "Retrived the gold" << endl;
        sleep(1);
        knowledge->qt_world->view->close();
    }


    //    kb->add_percept_to_heap(P_AGENT, kb->position_to_bits(position), x, y);
    kb->add_percept_to_heap(P_AGENT, kb->build_fcardinal(NORTH, x - 1, y), x, y);
    kb->add_percept_to_heap(P_AGENT, kb->build_fcardinal(SOUTH, x + 1, y), x, y);
    kb->add_percept_to_heap(P_AGENT, kb->build_fcardinal(EAST, x, y - 1), x, y);
    kb->add_percept_to_heap(P_AGENT, kb->build_fcardinal(WEST, x, y + 1), x, y);

    //add perceps to kb

    //        if ((next_tile & BREEZE) > 0) {
    //        kb->add_percept_to_heap(P_BREEZY, kb->position_to_bits(position), x, y);
    //    } else {
    //        kb->add_percept_to_heap(P_NEGATION | P_BREEZY, kb->position_to_bits(position), x, y);
    //    }

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
    //    search_tiles.clear();
    //    search_tiles.push_back(new Point(x, y));
    //    search_tiles.push_back(new Point(x + 1, y));
    //    search_tiles.push_back(new Point(x - 1, y));
    //    search_tiles.push_back(new Point(x, y + 1));
    //    search_tiles.push_back(new Point(x, y - 1));
    //    search_tiles.push_back(new Point(x + 1, y + 1));
    //    search_tiles.push_back(new Point(x + 1, y - 1));
    //    search_tiles.push_back(new Point(x - 1, y + 1));
    //    search_tiles.push_back(new Point(x - 1, y - 1));
    kb->heap_to_stack(search_tiles);


    //    if ((next_tile & STENCH) > 0) {
    //        add_const_clause(P_STENCH, position_to_bits(position));
    //    }

    x = position->x;
    y = position->y;

    //    infer_move(orientation);

    //    if (infer_pit(F_NORTH)) {
    //        knowledge->qt_world->set_tile(x, y + 1, POS_EMPTY);
    //    } else {
    //        knowledge->qt_world->set_tile(x, y + 1, POS_PIT);
    //    }
    //    if (infer_pit(F_SOUTH)) {
    //        knowledge->qt_world->set_tile(x, y - 1, POS_EMPTY);
    //    } else {
    //        knowledge->qt_world->set_tile(x, y - 1, POS_PIT);
    //    }
    //    if (infer_pit(F_EAST)) {
    //        knowledge->qt_world->set_tile(x + 1, y, POS_EMPTY);
    //    } else {
    //        knowledge->qt_world->set_tile(x + 1, y, POS_PIT);
    //    }
    //    if (infer_pit(F_WEST)) {
    //        knowledge->qt_world->set_tile(x - 1, y, POS_EMPTY);
    //    } else {
    //        knowledge->qt_world->set_tile(x - 1, y, POS_PIT);
    //    }
    //
    //
    //    if (infer_wumpus(F_NORTH)) {
    //        //        knowledge->qt_world->set_tile(x, y + 1, POS_EMPTY);
    //    } else {
    //        knowledge->qt_world->set_tile(x, y + 1, POS_WUM);
    //    }
    //    if (infer_wumpus(F_SOUTH)) {
    //        //        knowledge->qt_world->set_tile(x, y - 1, POS_EMPTY);
    //    } else {
    //        knowledge->qt_world->set_tile(x, y - 1, POS_WUM);
    //    }
    //    if (infer_wumpus(F_EAST)) {
    //        //        knowledge->qt_world->set_tile(x + 1, y, POS_EMPTY);
    //    } else {
    //        knowledge->qt_world->set_tile(x + 1, y, POS_WUM);
    //    }
    //    if (infer_wumpus(F_WEST)) {
    //        //        knowledge->qt_world->set_tile(x - 1, y, POS_EMPTY);
    //    } else {
    //        knowledge->qt_world->set_tile(x - 1, y, POS_WUM);
    //    }
    //
    //    if (infer_barrier(F_NORTH) == 1) {
    //        knowledge->qt_world->set_tile(x, y + 1, WALL);
    //    }
    //    if (infer_barrier(F_SOUTH) == 1) {
    //        knowledge->qt_world->set_tile(x, y - 1, WALL);
    //    }
    //    if (infer_barrier(F_EAST) == 1) {
    //        knowledge->qt_world->set_tile(x + 1, y, WALL);
    //    }
    //    if (infer_barrier(F_WEST) == 1) {
    //        knowledge->qt_world->set_tile(x - 1, y, WALL);
    //    }

    if (infer_clear(F_NORTH) == 1) {
        //        kb->add_percept_to_heap(P_ISCLEAR, kb->position_to_bits(neighbors[NORTH]), x, y);
        knowledge->qt_world->set_tile(x, y + 1, IS_CLEAR);
    } else {
        knowledge->qt_world->set_tile(x, y + 1, NOT_CLEAR);
    }
    if (infer_clear(F_SOUTH) == 1) {
        //        kb->add_percept_to_heap(P_ISCLEAR, kb->position_to_bits(neighbors[SOUTH]), x, y);
        knowledge->qt_world->set_tile(x, y - 1, IS_CLEAR);
    } else {
        knowledge->qt_world->set_tile(x, y - 1, NOT_CLEAR);
    }
    if (infer_clear(F_EAST) == 1) {
        //        kb->add_percept_to_heap(P_ISCLEAR, kb->position_to_bits(neighbors[EAST]), x, y);
        knowledge->qt_world->set_tile(x + 1, y, IS_CLEAR);
    } else {
        knowledge->qt_world->set_tile(x + 1, y, NOT_CLEAR);
    }
    if (infer_clear(F_WEST) == 1) {
        //        kb->add_percept_to_heap(P_ISCLEAR, kb->position_to_bits(neighbors[WEST]), x, y);
        knowledge->qt_world->set_tile(x - 1, y, IS_CLEAR);
    } else {
        knowledge->qt_world->set_tile(x - 1, y, NOT_CLEAR);
    }
}

uint Human_agent::infer_pit(uint direction) {


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

    //#if debug_mode
    //    cout << "The current knowledge base is:" << endl;
    //    kb->print_kb(kb->kb_time_stack);
    //    cout << endl;
    //
    //    cout << "We are trying to prove:" << endl;
    //    kb->print_clause(query);
    //    cout << endl << "*************************************" << endl;
    //#endif
    uint result = kb->input_resolution_bfs(query);
    //#if debug_mode
    //    cout << "The result is: " << result << endl;
    //#endif

    return result;

}

uint Human_agent::infer_wumpus(uint direction) {


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

    //#if debug_mode
    //    cout << "The current knowledge base is:" << endl;
    //    kb->print_kb(kb->kb_time_stack);
    //    cout << endl;
    //
    //    cout << "We are trying to prove:" << endl;
    //    kb->print_clause(query);
    //    cout << endl << "*************************************" << endl;
    //#endif
    uint result = kb->input_resolution_bfs(query);
    //#if debug_mode
    //    cout << "The result is: " << result << endl;
    //#endif

    return result;

}

uint Human_agent::infer_barrier(uint direction) {


    /* Build query */
    func_args fargs;
    uint position_bits = kb->position_to_bits(position);
    fargs.push_back(position_bits);
    func fquery = kb->build_func(direction, fargs);
    pred_args pquery_arg;
    pquery_arg.push_back(fquery);

    /* query for pits */
    pred p_query = kb->build_pred(P_WALL, pquery_arg);
    clause query;
    query.push_back(p_query);

    //#if debug_mode        cout << "The current knowledge base is:" << endl;
    kb->print_kb(kb->kb_time_stack);
    cout << endl;
    //    cout << "The current knowledge base is:" << endl;
    //    kb->print_kb(kb->kb_time_stack);
    //    cout << endl;
    //
    //    cout << "We are trying to prove:" << endl;
    //    kb->print_clause(query);
    //    cout << endl << "*************************************" << endl;
    //#endif
    uint result = kb->input_resolution_bfs(query);
    //#if debug_mode
    //    cout << "The result is: " << result << endl;
    //#endif

    return result;

}

uint Human_agent::infer_clear(uint direction) {


    /* Build query */
    func_args fargs;
    uint position_bits = kb->position_to_bits(position);
    fargs.push_back(position_bits);
    func fquery = kb->build_func(direction, fargs);
    pred_args pquery_arg;
    pquery_arg.push_back(fquery);

    /* query for pits */
    pred p_query = kb->build_pred(P_ISCLEAR, pquery_arg);
    clause query;
    query.push_back(p_query);

#if debug_mode
    //        cout << "The current knowledge base is:" << endl;
    //        kb->print_kb(kb->kb_time_stack);
    //        cout << endl;
    cout << "__________________________________________________________________" << endl;
    cout << "We are trying to prove:" << endl;
    kb->print_clause(query);
    cout << endl << "*************************************" << endl;
#endif
    uint result = kb->input_resolution_bfs(query);
    //#if debug_mode
    cout << "The result is: " << result << endl;
    //#endif

    return result;

}

uint Human_agent::find_right(uint dir) {
    switch (dir) {
        case EAST:
            return F_SOUTH;
        case NORTH:
            return F_EAST;
        case WEST:
            return F_NORTH;
        case SOUTH:
            return F_WEST;
    }
}

uint Human_agent::find_left(uint dir) {
    switch (dir) {
        case EAST:
            return F_NORTH;
        case NORTH:
            return F_WEST;
        case WEST:
            return F_SOUTH;
        case SOUTH:
            return F_EAST;
    }
}

uint Human_agent::find_forward(uint dir) {
    cout << "The current knowledge base is:" << endl;
    kb->print_kb(kb->kb_time_stack);
    cout << endl;
    switch (dir) {
        case EAST:
            return F_EAST;
        case NORTH:
            return F_NORTH;
        case WEST:
            return F_WEST;
        case SOUTH:
            return F_SOUTH;
    }
}

uint Human_agent::find_backward(uint dir) {
    switch (dir) {
        case EAST:
            return F_WEST;
        case NORTH:
            return F_SOUTH;
        case WEST:
            return F_EAST;
        case SOUTH:
            return F_NORTH;
    }
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
    if (infer_clear(find_right(orientation)) == TRUE) {
        //move backwards
        int x;
    } else if ((infer_clear(find_right(orientation)) == FALSE) and (infer_clear(find_forward(orientation)) == TRUE)) {
        //move forward
        int x;

    } else if ((infer_clear(find_right(orientation)) == FALSE) and (infer_clear(find_forward(orientation)) == FALSE)
            and (infer_clear(find_left(orientation)) == TRUE)) {
        //rotate and move left
        int x;

    } else if ((infer_clear(find_right(orientation)) == FALSE) and (infer_clear(find_forward(orientation)) == FALSE)) {
        //rotate left
        int x;
    } else if (infer_clear(find_forward(orientation)) == FALSE) {
        //rotate left
        int x;
    } else {
        int x;
    }






}

