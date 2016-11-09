/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "reactive_agent.h"                                                                                              
#include "engine.h"
#include <fstream>

Reactive_agent::Reactive_agent(Engine * this_engine, int sz, string filenames) {

    N = sz;

    // Initialize class variables
    vector<string> rule_files;
    rule_files.push_back("Rules/all_rules.txt");
    filename = filenames;
    knowledge = new World(sz, this);
    position = new Point(START_X, START_Y - 1);
    engine = this_engine;
    time = 0;
    take_risk = 0;
    orientation = NORTH;
    my_tile = knowledge->qt_world->set_tile(position->x, position->y, AGENT);

    // ask the engine to be placed at the start position
    make_move(NORTH);
    run_test();




}

void Reactive_agent::output_stats(uint gold) {
    ofstream myfile;
    myfile.open(filename, std::ios::out | std::ios::app);
     
    myfile << N << " " << engine->num_obstacles() << " " << engine->score << " " << endl;
    cout << N << " " << engine->num_obstacles() << " " << engine->score << " " << endl;
    
    
}

void Reactive_agent::run_test() {
    while(make_move(next_move));
}

bool Reactive_agent::make_move(int direction) {



    int next_tile = engine->move(direction, position);
    int x;
    int y;
    neighbors = knowledge->find_neighbors(position);
    if ((next_tile & WALL) > 0) {


        x = neighbors[direction]->x;
        y = neighbors[direction]->y;
        next_tile = (next_tile | NOT_CLEAR);




    } else {

        x = position->x;
        y = position->y;
        next_tile = (next_tile | IS_CLEAR);
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
        output_stats(0);
        sleep(1);
        knowledge->qt_world->view->close();
        return false;
    } else if ((next_tile & PIT) > 0) {
        cout << "Fell into a pit" << endl;
        output_stats(0);
        sleep(1);
        knowledge->qt_world->view->close();
        return false;
    } else if ((next_tile & GOLD) > 0) {
        engine->score = engine->score + 1000;
        cout << "Retrived the gold" << endl;
        output_stats(1);
        sleep(1);
        knowledge->qt_world->view->close();
        return false;
    }





    x = position->x;
    y = position->y;

    /*if stinky or breezy:
     *    pick is clear neighbor random is_clear
     *       if none exist:
     *            pick total random
     * else:
     *      pick random not is_clear
     *      then pick random thats is_clear and not not clear
     */
    if ((knowledge->world_vec[x][y] & STENCH) || (knowledge->world_vec[x][y] & BREEZE)) {
        s_or_b_pick();

    } else {
        pick();
    }

    return true;


}

void Reactive_agent::s_or_b_pick() {
    //case for handling if spot is stinky or breezy

    if (take_risk > 500) {
        //If an undiscovered spot has not been discovered in 300 moves take a risk
        vector<uint> clear_adj;
        for (uint i = 0; i < neighbors.size(); i++) {
            if (!(knowledge->world_vec[neighbors[i]->x][neighbors[i]->y] & IS_CLEAR)&&(!(knowledge->world_vec[neighbors[i]->x][neighbors[i]->y] & NOT_CLEAR))) {
                clear_adj.push_back(i);
            }
        }

        if (clear_adj.size() > 0) {
            int r = rand() % clear_adj.size();
            next_move = clear_adj[r];
        } else {
            //pick a random square
            int r = rand() % neighbors.size();
            next_move = r;
        }
    } else {


        vector<uint> clear_adj;
        //find all adjacent squares that are marked clear and not marked not_clear
        for (uint i = 0; i < neighbors.size(); i++) {
            if (knowledge->world_vec[neighbors[i]->x][neighbors[i]->y] & IS_CLEAR && (!(knowledge->world_vec[neighbors[i]->x][neighbors[i]->y] & NOT_CLEAR))) {
                clear_adj.push_back(i);
            }
        }

        //pick a random clear square
        if (clear_adj.size() > 0) {
            int r = rand() % clear_adj.size();
            next_move = clear_adj[r];
        } else {
            //pick a random square
            int r = rand() % neighbors.size();
            next_move = r;
        }
    }
}

void Reactive_agent::pick() {
    //handles case where current square does not have a breeze or a stench
    vector<uint> n_clear_adj;

    for (uint i = 0; i < neighbors.size(); i++) {
        //if a square is not marked clear and not marked not clear, add to possible moves
        if (!(knowledge->world_vec[neighbors[i]->x][neighbors[i]->y] & IS_CLEAR)&&(!(knowledge->world_vec[neighbors[i]->x][neighbors[i]->y] & NOT_CLEAR))) {
            n_clear_adj.push_back(i);
        }
    }
    //if there are unexplored adject squares randomly choose one
    if (n_clear_adj.size() > 0) {
        int r = rand() % n_clear_adj.size();
        next_move = n_clear_adj[r];
        take_risk = 0;

    } else {
        take_risk++;
        //pick a square that IS_CLEAR and not NOT_CLEAR
        vector<uint> nn_clear_adj;
        for (uint i = 0; i < neighbors.size(); i++) {

            if ((knowledge->world_vec[neighbors[i]->x][neighbors[i]->y] & IS_CLEAR)&&(!(knowledge->world_vec[neighbors[i]->x][neighbors[i]->y] & NOT_CLEAR))) {
                nn_clear_adj.push_back(i);

            }
        }

        int r = rand() % nn_clear_adj.size();
        next_move = nn_clear_adj[r];
    }
}

uint Reactive_agent::find_right(uint dir) {
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

uint Reactive_agent::find_left(uint dir) {
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

uint Reactive_agent::find_forward(uint dir) {
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

uint Reactive_agent::find_backward(uint dir) {
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








