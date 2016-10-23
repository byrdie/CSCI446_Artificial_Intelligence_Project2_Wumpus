/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   logic_agent.h
 * Author: byrdie
 *
 * Created on October 23, 2016, 2:40 PM
 */

#ifndef LOGIC_AGENT_H
#define LOGIC_AGENT_H

class Logic_agent;

#include "typedef.h"
#include "world_gen.h"
#include "engine.h"
#include "knowledge.h"

class Logic_agent {
public:
    uint N;
    Point * position;
    World * knowledge;
    Knowledge * kb;
    Engine * engine;
    QGraphicsPixmapItem * my_tile;
    vector<Point *> search_tiles;
    vector<Point *> neighbors;
    
    bool clearN;
    bool clearS;
    bool clearE;
    bool clearW;
    
    vector<int> move_stack;
    
    uint orientation;
    Logic_agent(Engine * this_engine, int N);
    
    void make_move();
//    vector<bool> infer(uint direction);
    uint find_right(uint dir);
    uint find_left(uint dir);
    uint find_forward(uint dir);
    uint find_backward(uint dir);
    clause create_clause(uint predicate, vector<uint> function,  vector<uint> constant);
    void execute_rhr();
    
    uint infer_pit(uint direction);
    uint infer_wumpus(uint direction);
    uint infer_barrier(uint direction);
    uint infer_clear(uint direction);
    
//    bool infer_move(uint direction);
    
    void init_kb();
    bool AdjExplored(Point * pos);
    bool is_clear(Point pos);
};

#endif /* LOGIC_AGENT_H */

