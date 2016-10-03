/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "engine.h"

Engine::Engine(World * this_world) {
    world = this_world;
}

int Engine::move(int direction, Point * cur_pos) {

    vector<Point *> neighbors = world->find_neighbors(cur_pos);

    Point * test_pt = neighbors[direction];

    int test_tile = world->world_vec[test_pt->x][test_pt->y];

    if ((test_tile & WALL) > 0){
        return test_tile;
    } else {
        cur_pos->x = test_pt->x;
        cur_pos->y = test_pt->y;
    }
    return test_tile;

}