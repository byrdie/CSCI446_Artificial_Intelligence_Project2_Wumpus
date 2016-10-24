/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reactive_agent.h
 * Author: byrdie
 *
 * Created on October 23, 2016, 11:39 AM
 */

#ifndef REACTIVE_AGENT_H
#define REACTIVE_AGENT_H
class Reactive_agent;

#include "typedef.h"
#include "world_gen.h"
#include "engine.h"
#include "knowledge.h"

class Reactive_agent {
public:
    uint N;
    Point * position;
    World * knowledge;
    Engine * engine;
    QGraphicsPixmapItem * my_tile;
    vector<Point *> search_tiles;
    vector<Point *> neighbors;
    uint time;
    uint orientation;
    uint next_move;
    uint take_risk;
    Reactive_agent(Engine * this_engine, int N);
    
    void make_move(int direction);
//    vector<bool> infer(uint direction);
    uint find_right(uint dir);
    uint find_left(uint dir);
    uint find_forward(uint dir);
    uint find_backward(uint dir);
    void s_or_b_pick();
    void pick();
    
//    bool infer_move(uint direction);
    

    bool AdjExplored(Point * pos);
    bool is_clear(Point pos);
};


#endif /* REACTIVE_AGENT_H */

