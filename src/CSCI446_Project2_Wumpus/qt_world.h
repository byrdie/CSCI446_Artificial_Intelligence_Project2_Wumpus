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

#ifndef QT_WORDL_H
#define QT_WORDL_H

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

#include "typedef.h"

using namespace std;

class Qt_world;
class World_view;

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
    QPixmap * base_wall_sprite;
    QPixmap * base_hero_sprite;
    QPixmap * base_wumpus_sprite;
    QPixmap * base_stench_sprite;
    QPixmap * base_pit_sprite;
    QPixmap * base_breeze_sprite;
    QPixmap * base_gold_sprite;
    QPixmap * base_fog_sprite;
    
    // Dictionary between sprites and bits
    map<int, QPixmap *> sprite_map;
    
    // Array to store mappings between coordinates and locations on screen
    std::vector<std::vector<Point*> > ind2win;

    // These need to be in the player class
    Point * p;
    QGraphicsPixmapItem * hero_tile;

    // Constructor
    Qt_world(int num_tiles);
    
    void set_tile(int x, int y, int z, int elem_bits);


};

class World_view : public QGraphicsView {
public:
    World_view(QGraphicsScene * scene);

private:
//    void keyPressEvent(QKeyEvent * e);
};


#endif /* QT_WORDL_H */

