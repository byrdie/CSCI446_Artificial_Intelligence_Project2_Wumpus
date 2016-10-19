/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   world_gen.h
 * Author: byrdie
 *
 * Created on October 2, 2016, 11:31 AM
 */

#ifndef WORLD_GEN_H
#define WORLD_GEN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

class World;

#include "qt_world.h"
#include "typedef.h"

#define START_X 1
#define START_Y 1

using namespace std;



class World {
public:
    int N;
    int num_wumpi;
    int num_pits;
    int num_barriers;
    vector<vector<int> > world_vec;
    
    Qt_world * qt_world;
    
    // Points describing location of various obstacles
    vector<Point*> wumpus_list;
    vector<Point*> pit_list;
    vector<Point*> barrier_list;
    vector<Point*> gold_list;
    
    World(int side_length, Agent * agent);   // Create a new world covered in fog
    World(int side_length, int n_wumpi, int n_pit, int n_barrier); // Create a new master world
    World(char * filename);     // Load a world from a file
    bool tile_is_empty(Point * p);
    Point * add_element(int elem);
    vector<Point *> add_effect(Point * center, int effect_bits);
    vector<Point *> find_neighbors(Point * center);
    
};

#endif /* WORLD_GEN_H */

