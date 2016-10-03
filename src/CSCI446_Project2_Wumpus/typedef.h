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

#define FOG     0x00000000
#define GOLD    0x00000001
#define WUMPUS  0x00000002
#define STENCH  0x00000004
#define PIT     0x00000008
#define BREEZE  0x0000000F
#define WALL    0x00000010
#define EMPTY   0x00000020
#define AGENT   0x00000040


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

