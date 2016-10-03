/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//class Gameboard : public QGraphicsView {
//public:

#include "qt_world.h"

using namespace std;

Qt_world::Qt_world(int num_tiles) {

    // Initialize variables
    N = num_tiles;
    win_sz = 500;
    scale = win_sz / num_tiles;
    p = new Point(1, 1);

    // Initialize Qt variables
    scene = new QGraphicsScene(0, 0, win_sz, win_sz);
    view = new World_view(scene);
    base_bg_sprite = new QPixmap("sprites/cobble.png");
    base_wall_sprite = new QPixmap("sprites/wall.png");
    base_hero_sprite = new QPixmap("sprites/hero.png");
    base_wumpus_sprite = new QPixmap("sprites/wumpus.png");
    base_stench_sprite = new QPixmap("sprites/stench3.png");
    base_pit_sprite = new QPixmap("sprites/pit.png");
    base_breeze_sprite = new QPixmap("sprites/breeze.png");
    base_gold_sprite = new QPixmap("sprites/gold.png");
    base_fog_sprite = new QPixmap("sprites/fog.png");

    // Initialize map between bits and sprites
    sprite_map[FOG] = base_fog_sprite;
    sprite_map[GOLD] = base_gold_sprite;
    sprite_map[WUMPUS] = base_wumpus_sprite;
    sprite_map[STENCH] = base_stench_sprite;
    sprite_map[PIT] = base_pit_sprite;
    sprite_map[BREEZE] = base_breeze_sprite;
    sprite_map[WALL] = base_wall_sprite;
    sprite_map[EMPTY] = base_bg_sprite;
    sprite_map[AGENT] = base_hero_sprite;


    hero_tile = new QGraphicsPixmapItem(0, scene);

    // Construct map between indices and screen position
    for (int i = 0; i < N + 2; i++) {
        vector<Point*> ind2win_row;
        for (int j = 0; j < N + 2; j++) {
            ind2win_row.push_back(new Point(i* scale, j * scale));
        }
        ind2win.push_back(ind2win_row);
    }


//    for (int i = 0; i < N + 2; i++) {
//        for (int j = 0; j < N + 2; j++) {
//            QPixmap * bg_sprite = new QPixmap(base_bg_sprite->scaled(scale, scale, Qt::KeepAspectRatio));
//            QGraphicsPixmapItem * bg_tile = new QGraphicsPixmapItem(0, scene);
//            bg_tile->setPixmap(*bg_sprite);
//            bg_tile->setPos(ind2win[i][j]->x, ind2win[i][j]->y);
//            bg_tile->setZValue(0);
//
//            if (i == 0 or i == N + 1 or j == 0 or j == N + 1) {
//                QPixmap * wall_sprite = new QPixmap(base_wall_sprite->scaled(scale, scale, Qt::KeepAspectRatio));
//                QGraphicsPixmapItem * wall_tile = new QGraphicsPixmapItem(0, scene);
//                wall_tile->setPixmap(*wall_sprite);
//                wall_tile->setPos(ind2win[i][j]->x, ind2win[i][j]->y);
//                wall_tile->setZValue(1);
//            }
//        }
//    }
//
//
//
//
//
//
//    QPixmap * hero_sprite = new QPixmap(base_hero_sprite->scaled(scale, scale, Qt::KeepAspectRatio));
//
//    hero_tile->setPixmap(*hero_sprite);
//    hero_tile->setPos(ind2win[p->x][p->y]->x, ind2win[p->x][p->y]->y);
//    hero_tile->setZValue(2);



}

void Qt_world::set_tile(int x, int y, int z, int elem_bits) {
    
    QPixmap * base_sprite = sprite_map[elem_bits];
            
    QPixmap * sprite = new QPixmap(base_sprite->scaled(scale, scale, Qt::KeepAspectRatio));
    QGraphicsPixmapItem * bg_tile = new QGraphicsPixmapItem(0, scene);
    bg_tile->setPixmap(*sprite);
    bg_tile->setPos(ind2win[x][y]->x, ind2win[x][y]->y);
    bg_tile->setZValue(z);
}

/**
 * The World View class exists to extend the QGraphicsView class. Its primary function
 * is to overwrite the keyPressEvents to provide input for human players
 * @param scene
 */
World_view::World_view(QGraphicsScene * scene) : QGraphicsView(scene) {
    cout << "constructed view" << endl;
}

//void World_view::keyPressEvent(QKeyEvent * e) {
//
//
//    switch (e->key()) {
//        case Qt::Key_A: p->x = p->x - 1;
//            break;
//        case Qt::Key_S: p->y = p->y + 1;
//            break;
//        case Qt::Key_W: p->y = p->y - 1;
//            break;
//        case Qt::Key_D: p->x = p->x + 1;
//            break;
//        default:
//            std::cout << "invalid input" << std::endl;
//    }
//    hero_tile->setPos(ind2win[p->x][p->y]->x, ind2win[p->x][p->y]->y);
//    //        qApp->processEvents();
//
//    QGraphicsView::keyPressEvent(e);
//}

