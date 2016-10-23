/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Qt_wordl.h
 * Author: byrdie
 *
 * Created on October 1, 2016, 9:53 PM
 */

#ifndef QT_WORLD_H
#define QT_WORLD_H

#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <stdio.h>
#include <map>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <qt5/QtGui/qpixmap.h>
#include <QRect>
#include <vector>
#include <QKeyEvent>
#include <qt5/QtWidgets/qwidget.h>

class Qt_world;
class World_view;

#include "typedef.h"
#include "human_agent.h"

using namespace std;


class Qt_world {
public:
    int N;
    int win_sz;
    int scale;
    
    // Qt display variables
    QGraphicsScene * scene;
    World_view * view;
    
    // Qt pixelmaps of sprites
    QPixmap * base_bg_sprite;
    QPixmap * base_p_cobble_sprite;
    QPixmap * base_wall_sprite;
    QPixmap * base_hero_sprite;
    QPixmap * base_wumpus_sprite;
    QPixmap * base_p_wumpus_sprite;
    QPixmap * base_stench_sprite;
    QPixmap * base_pit_sprite;
    QPixmap * base_p_pit_sprite;
    QPixmap * base_breeze_sprite;
    QPixmap * base_gold_sprite;
    QPixmap * base_fog_sprite;
    QPixmap * base_clear_sprite;
    QPixmap * base_not_clear_sprite;
    
    // Dictionary between sprites and bits
    map<int, QPixmap *> sprite_map;
    map<int, int> height_map;
    
    // Array to store mappings between coordinates and locations on screen
    std::vector<std::vector<Point*> > ind2win;

    // Constructor
    Qt_world(int num_tiles);
    Qt_world(int num_tiles, Human_agent * h_agent);
    void init_map();
    
    QGraphicsPixmapItem *  set_tile(int x, int y, int elem_bits);
    void move_tile(QGraphicsPixmapItem * tile, int x, int y);


};

class World_view : public QGraphicsView {
public:
    
    Human_agent * agent;
    
    World_view(QGraphicsScene * scene, Human_agent * h_agent);
    World_view(QGraphicsScene * scene);
    

private:
    void keyPressEvent(QKeyEvent * e);
};


#endif /* QT_WORDL_H */

