/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   human_agent.h
 * Author: byrdie
 *
 * Created on October 2, 2016, 8:49 PM
 */

#ifndef HUMAN_AGENT_H
#define HUMAN_AGENT_H


class Human_agent;
#include "typedef.h"
#include "world_gen.h"
#include "engine.h"
#include "knowledge.h"

class Human_agent {
public:
    uint N;
    Point * position;
    World * knowledge;
    Knowledge * kb;
    Engine * engine;
    QGraphicsPixmapItem * my_tile;
    vector<Point *> search_tiles;
    
    uint time;
    
    uint orientation;
    Human_agent(Engine * this_engine, int N);
    
    void make_move(int direction);
    bool infer(uint direction);
    apoint find_right(Point * pos, uint dir);
    apoint find_left(Point * pos, uint dir);
    apoint find_forward(Point * pos, uint dir);
    apoint find_backward(Point * pos, uint dir);
    clause create_clause(uint predicate, vector<uint> function,  vector<uint> constant);
    void execute_rhr();
    
    infer_explored();
    bool infer_move(uint direction);
    
    void init_kb();
};


#endif /* HUMAN_AGENT_H */
