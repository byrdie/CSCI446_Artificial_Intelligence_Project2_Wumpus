/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reasoning_agent.h
 * Author: byrdie
 *
 * Created on October 19, 2016, 10:15 AM
 */

#ifndef REASONING_AGENT_H
#define REASONING_AGENT_H
class Reasoning_agent;
#include "typedef.h"
#include "world_gen.h"
#include "engine.h"


class Reasoning_agent {
public:
    Point * position;
    World * knowledge;
    Engine * engine;
    QGraphicsPixmapItem * my_tile;
    
    Reasoning_agent(Engine * this_engine, int N);
    
    void make_move(int direction);
    
};


#endif /* REASONING_AGENT_H */

