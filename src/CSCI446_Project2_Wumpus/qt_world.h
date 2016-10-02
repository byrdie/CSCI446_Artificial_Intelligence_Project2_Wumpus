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


class Qt_world : public QGraphicsView {
    
public:
    int N;
    int win_sz;
    int scale;
    std::vector<std::vector<Point*> > ind2win;
    
    // These need to be in the player class
    Point * p;
    QGraphicsPixmapItem * hero_tile;
    
    Qt_world(QGraphicsScene * scene, int num_tiles, int window_sz);
    
private:
    void keyPressEvent(QKeyEvent * e);
};

#endif /* QT_WORDL_H */

