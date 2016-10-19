/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   agent.h
 * Author: byrdie
 *
 * Created on October 19, 2016, 10:57 AM
 */

#ifndef AGENT_H
#define AGENT_H
class Agent;
#include "world_gen.h"
#include "engine.h"


class Agent {
public:
    Point * position;
    World * knowledge;
    Engine * engine;
    QGraphicsPixmapItem * my_tile;
    
    Agent(Engine * this_engine, int N);
    
    void make_move(int direction);
    
};


#endif /* AGENT_H */

