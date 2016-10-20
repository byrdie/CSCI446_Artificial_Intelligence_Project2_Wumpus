#include "human_agent.h"
#include "engine.h"

Human_agent::Human_agent(Engine * this_engine, int N) {

    // Initialize class variables
    kb = new Knowledge("../Rules/pit_rules.txt");
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
        add_const_clause(P_WALL, position_to_bits(neighbors[direction]));

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
        add_const_clause(P_BREEZE, position_to_bits(position));
    } else {
        add_const_clause(P_NEGATION | P_BREEZE, position_to_bits(position));
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
    uint position_bits = position_to_bits(position);
    fargs.push_back(position_bits);
    func fquery = kb->build_func(direction, fargs);
    pred_args pquery_arg;
    pquery_arg.push_back(fquery);
    pred p_query = kb->build_pred(P_NEGATION | P_PIT, pquery_arg);
    clause query;
    query.push_back(p_query);

    cout << "The current knowledge base is:" << endl;
    kb->print_kb(kb->static_kb);
    cout << endl;

    cout << "We are trying to prove:" << endl;
    kb->print_clause(query);
    cout << endl << "*************************************" << endl;

    cnf neg_query = kb->negate_clause(query);
    bool result = kb->linear_resolution(kb->static_kb, neg_query[0], 0);

    cout << "The result is: " << result << endl;

    return result;

}

void Human_agent::add_const_clause(uint predicate, uint arg) {

    func_args fargs;
    fargs.push_back(arg);
    func fcon = kb->build_func(F_CONST, fargs);
    pred_args pargs;
    pargs.push_back(fcon);
    pred pcon = kb->build_pred(predicate, pargs);
    clause rule;
    rule.push_back(pcon);
    for (uint i = 0; i < kb->static_kb.size(); i++) {
        if (kb->clause_eq(rule, kb->static_kb[i])) {
            return;
        }
    }
    kb->static_kb.insert(kb->static_kb.begin(), rule);
}

/**
 * 
 * @param predicate
 * @param arg1 
 * @param arg2
 */
void Human_agent::add_const_clause(uint predicate, uint arg1, uint arg2) {

    func_args fargs1;
    func_args fargs2;
    fargs1.push_back(arg1);
    fargs2.push_back(arg2);
    func fcon1 = kb->build_func(F_CONST, fargs1);
    func fcon2 = kb->build_func(F_CONST, fargs2);
    pred_args pargs;
    pargs.push_back(fcon1);
    pargs.push_back(fcon2);
    pred pcon = kb->build_pred(predicate, pargs);
    clause rule;
    rule.push_back(pcon);
    for (uint i = 0; i < kb->static_kb.size(); i++) {
        if (kb->clause_eq(rule, kb->static_kb[i])) {
            return;
        }
    }
    kb->static_kb.insert(kb->static_kb.begin(), rule);
}

