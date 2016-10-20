/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   typedef.h
 * Author: byrdie
 *
 * Created on October 1, 2016, 10:26 PM
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H

// Tile types
#define FOG     0x00000000
#define GOLD    0x00000001
#define WUMPUS  0x00000002
#define STENCH  0x00000004
#define PIT     0x00000008
#define BREEZE  0x00000080
#define WALL    0x00000010
#define EMPTY   0x00000020
#define AGENT   0x00000040
#define POS_PIT   0x00000080
#define POS_EMPTY 0x00000100

// Definite move types
#define EAST    0
#define NORTH   1
#define WEST    2
#define SOUTH   3

class Point {
public:
    int x;
    int y;

    Point(float xpos, float ypos) {
        x = xpos;
        y = ypos;
    }
};

#endif /* TYPEDEF_H */

