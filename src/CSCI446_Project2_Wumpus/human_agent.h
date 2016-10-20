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
    Point * position;
    World * knowledge;
    Knowledge * kb;
    Engine * engine;
    QGraphicsPixmapItem * my_tile;
    
    Human_agent(Engine * this_engine, int N);
    
    void make_move(int direction);
    void add_const_clause(uint predicate, uint arg);
};
uint position_to_bits(Point * position);
vector<int> bits_to_position (uint bits);

#endif /* HUMAN_AGENT_H */