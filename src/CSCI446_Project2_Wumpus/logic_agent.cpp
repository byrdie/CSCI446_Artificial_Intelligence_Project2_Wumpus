#include "logic_agent.h"
#include "engine.h"

Logic_agent::Logic_agent(Engine * this_engine, int sz, string file) {

    N = sz;

    // Initialize class variables
    vector<string> rule_files;
    rule_files.push_back("Rules/all_rules.txt");
    kb = new Knowledge(sz, rule_files);
    knowledge = new World(sz, this);
    position = new Point(START_X, START_Y - 1);
    engine = this_engine;
    filename = file;

    orientation = NORTH;
    my_tile = knowledge->qt_world->set_tile(position->x, position->y, AGENT);
    // ask the engine to be placed at the start position
    clearN = true;

    make_move();
    kb->print_kb(&kb->out, kb->kb_rules);



}

void Logic_agent::make_move() {

    while (true) {

        int x = position->x;
        int y = position->y;

        int direction;

        /* Determine next move */

        if (clearN and knowledge->world_vec[x][y + 1] == FOG) {
            move_stack.push_back(SOUTH);
            direction = NORTH;
        } else if (clearE and knowledge->world_vec[x + 1][y] == FOG) {
            move_stack.push_back(WEST);
            direction = EAST;
        } else if (clearW and knowledge->world_vec[x - 1][y] == FOG) {
            move_stack.push_back(EAST);
            direction = WEST;
        } else if (clearS and knowledge->world_vec[x][y - 1] == FOG) {
            move_stack.push_back(NORTH);
            direction = SOUTH;
        } else {
            cout << move_stack.size() << endl;
            if (move_stack.size() > 0) {
                direction = move_stack.back();
                cout << "popping " << direction << " off the stack" << endl;
                move_stack.pop_back();
            } else {
                direction = rand() % 4;
                //                    move_stack.push_back((direction + 2)%4);
                cout << "choosing random direction " << direction << endl;
            }
        }



        int next_tile = engine->move(direction, position);

        neighbors = knowledge->find_neighbors(position);
        if ((next_tile & WALL) > 0) {

            if (move_stack.size() != 0) {
                move_stack.pop_back();
            }


            x = neighbors[direction]->x;
            y = neighbors[direction]->y;
            kb->clear_heap(x, y);

            kb->clear_stack();

            //add wall clause to kb
            //        kb->add_percept_to_heap(P_WALL, kb->build_fcardinal(direction, position->x, position->y), x, y);
            kb->add_percept_to_heap(P_WALL, kb->build_fcardinal(EAST, x - 1, y), x, y);
            kb->add_percept_to_heap(P_WALL, kb->build_fcardinal(WEST, x + 1, y), x, y);
            kb->add_percept_to_heap(P_WALL, kb->build_fcardinal(NORTH, x, y - 1), x, y);
            kb->add_percept_to_heap(P_WALL, kb->build_fcardinal(SOUTH, x, y + 1), x, y);

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


        x = position->x;
        y = position->y;

        knowledge->qt_world->move_tile(my_tile, position->x, position->y);
        knowledge->qt_world->set_tile(x - 1, y, IS_CLEAR);


        if ((next_tile & WUMPUS) > 0) {
            cout << "Killed by a Wumpus" << endl;
            output_stats(0);
            sleep(1);
            knowledge->qt_world->view->close();
            return;
        }

        if ((next_tile & PIT) > 0) {
            cout << "Fell into a pit" << endl;
            output_stats(0);
            sleep(1);
            knowledge->qt_world->view->close();
            return;
        }
        if ((next_tile & GOLD) > 0) {
            engine->score = engine->score + 1000;
            output_stats(1);
            cout << "Retrived the gold" << endl;
            sleep(1);
            knowledge->qt_world->view->close();
            return;
        }


        //    kb->add_percept_to_heap(P_AGENT, kb->position_to_bits(position), x, y);

        kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(EAST, x - 1, y), x, y);
        kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(WEST, x + 1, y), x, y);
        kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(NORTH, x, y - 1), x, y);
        kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(SOUTH, x, y + 1), x, y);

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

        search_tiles.clear();
        search_tiles.push_back(new Point(x, y));
        search_tiles.push_back(new Point(x + 1, y));
        search_tiles.push_back(new Point(x - 1, y));
        search_tiles.push_back(new Point(x, y + 1));
        search_tiles.push_back(new Point(x, y - 1));
        kb->heap_to_stack(search_tiles);

        clearN = infer_clear(F_NORTH) == 1;
        clearS = infer_clear(F_SOUTH) == 1;
        clearE = infer_clear(F_EAST) == 1;
        clearW = infer_clear(F_WEST) == 1;
        if (clearN) {
            knowledge->qt_world->set_tile(x, y + 1, IS_CLEAR);
            uint u = x;
            uint v = y + 1;
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(EAST, u - 1, v), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(WEST, u + 1, v), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(NORTH, u, v - 1), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(SOUTH, u, v + 1), u, v);
            //        kb->add_percept_to_heap(P_ISCLEAR, kb->position_to_bits(neighbors[NORTH]), x, y);

        } else {
            knowledge->qt_world->set_tile(x, y + 1, NOT_CLEAR);
        }
        if (clearS) {
            knowledge->qt_world->set_tile(x, y - 1, IS_CLEAR);
            uint u = x;
            uint v = y - 1;
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(EAST, u - 1, v), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(WEST, u + 1, v), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(NORTH, u, v - 1), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(SOUTH, u, v + 1), u, v);
            //        kb->add_percept_to_heap(P_ISCLEAR, kb->position_to_bits(neighbors[SOUTH]), x, y);

        } else {
            knowledge->qt_world->set_tile(x, y - 1, NOT_CLEAR);
        }
        if (clearE) {
            knowledge->qt_world->set_tile(x + 1, y, IS_CLEAR);
            uint u = x + 1;
            uint v = y;
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(EAST, u - 1, v), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(WEST, u + 1, v), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(NORTH, u, v - 1), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(SOUTH, u, v + 1), u, v);
            //        kb->add_percept_to_heap(P_ISCLEAR, kb->position_to_bits(neighbors[EAST]), x, y);

        } else {
            knowledge->qt_world->set_tile(x + 1, y, NOT_CLEAR);
        }
        if (clearW) {
            knowledge->qt_world->set_tile(x - 1, y, IS_CLEAR);
            uint u = x - 1;
            uint v = y;
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(EAST, u - 1, v), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(WEST, u + 1, v), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(NORTH, u, v - 1), u, v);
            kb->add_percept_to_heap(P_ISCLEAR, kb->build_fcardinal(SOUTH, u, v + 1), u, v);
            //        kb->add_percept_to_heap(P_ISCLEAR, kb->position_to_bits(neighbors[WEST]), x, y);

        } else {

            knowledge->qt_world->set_tile(x - 1, y, NOT_CLEAR);
        }

        qApp->processEvents();
        qApp->processEvents();

        char * filename = new char[100];
        sprintf(filename, "../output/frames/%d.png", time);
        knowledge->qt_world->save_world(filename);

        char latex_image[100];
        sprintf(latex_image, "     \\includegraphics[width=0.5\\textwidth]{frames/%d.png}", time);

        kb->latex << "\\begin{center}" << endl;
        kb->latex << latex_image << endl;
        kb->latex << "\\end{center}" << endl;

        time++;
    }

}

uint Logic_agent::infer_clear(uint direction) {


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
    //    cout << "The current knowledge base is:" << endl;
    //    kb->print_kb(kb->kb_time_stack);
    kb->out << endl;
    kb->out << "__________________________________________________________________" << endl;
    kb->out << "We are trying to prove:" << endl;
    kb->print_clause(&kb->out, query);
    kb->out << endl;
    kb->out << "__________________________________________________________________" << endl;

    kb->latex << endl;
    kb->latex << "\\hrulefill \\\\" << endl;
    kb->latex << "\\texttt{We are trying to prove:} \\\\" << endl;
    kb->latex << "\\texttt{";
    kb->print_clause(&kb->latex, query);
    kb->latex << "} \\\\" << endl;
#endif
    uint result = kb->input_resolution_bfs(query);
#if debug_mode
    kb->out << "The result is: " << result << endl;
    kb->latex << "\\texttt{The result is: " << result << "} \\\\" << endl;
#endif

    return result;

}

clause Logic_agent::create_clause(uint predicate, vector<uint> function, vector<uint> constant) {
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

void Logic_agent::output_stats(uint gold) {
    ofstream myfile;
    myfile.open(filename, std::ios::out | std::ios::app);

    myfile << N << " " << engine->num_obstacles() << " " << engine->score << " " << endl;
    cout << N << " " << engine->num_obstacles() << " " << engine->score << " " << endl;
}



