/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//class Gameboard : public QGraphicsView {
//public:

#include "qt_world.h"

using namespace std;

Qt_world::Qt_world(QGraphicsScene * scene, int num_tiles, int window_sz) : QGraphicsView(scene){

    N = num_tiles;
    win_sz = window_sz;
    scale = win_sz / num_tiles;
    p = new Point(1, 1);

    

    hero_tile = new QGraphicsPixmapItem(0, scene);

    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);
    for (int i = 0; i < N + 2; i++) {
        vector<Point*> ind2win_row;
        for (int j = 0; j < N + 2; j++) {
            ind2win_row.push_back(new Point(i* scale, j * scale));
        }
        ind2win.push_back(ind2win_row);
    }

    QPixmap * orig_bg_sprite = new QPixmap("sprites/cobble.png");
    QPixmap * orig_wall_sprite = new QPixmap("sprites/wall.png");


    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < N + 2; j++) {
            QPixmap * bg_sprite = new QPixmap(orig_bg_sprite->scaled(scale, scale, Qt::KeepAspectRatio));
            QGraphicsPixmapItem * bg_tile = new QGraphicsPixmapItem(0, scene);
            bg_tile->setPixmap(*bg_sprite);
            bg_tile->setPos(ind2win[i][j]->x, ind2win[i][j]->y);
            bg_tile->setZValue(0);

            if (i == 0 or i == N + 1 or j == 0 or j == N + 1) {
                QPixmap * wall_sprite = new QPixmap(orig_wall_sprite->scaled(scale, scale, Qt::KeepAspectRatio));
                QGraphicsPixmapItem * wall_tile = new QGraphicsPixmapItem(0, scene);
                wall_tile->setPixmap(*wall_sprite);
                wall_tile->setPos(ind2win[i][j]->x, ind2win[i][j]->y);
                wall_tile->setZValue(1);
            }
        }
    } 





    QPixmap * orig_hero_sprite = new QPixmap("sprites/hero.png");
    QPixmap * hero_sprite = new QPixmap(orig_hero_sprite->scaled(scale, scale, Qt::KeepAspectRatio));

    hero_tile->setPixmap(*hero_sprite);
    hero_tile->setPos(ind2win[p->x][p->y]->x, ind2win[p->x][p->y]->y);
    hero_tile->setZValue(2);



}


void Qt_world::keyPressEvent(QKeyEvent * e) {


    switch (e->key()) {
        case Qt::Key_A: p->x = p->x - 1;
            break;
        case Qt::Key_S: p->y = p->y + 1;
            break;
        case Qt::Key_W: p->y = p->y - 1;
            break;
        case Qt::Key_D: p->x = p->x + 1;
            break;
        default:
            std::cout << "invalid input" << std::endl;
    }
    hero_tile->setPos(ind2win[p->x][p->y]->x, ind2win[p->x][p->y]->y);
    //        qApp->processEvents();

    QGraphicsView::keyPressEvent(e);
}

