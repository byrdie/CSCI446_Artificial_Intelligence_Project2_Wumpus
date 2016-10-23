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
    win_sz = 1000;
    scale = win_sz / (num_tiles + 2);

    // Initialize Qt variables
    scene = new QGraphicsScene(0, 0, win_sz, win_sz);
    view = new World_view(scene);
    view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    view->resize(win_sz,win_sz);
    init_map();

}

Qt_world::Qt_world(int num_tiles, Logic_agent * h_agent) {
    // Initialize variables
    N = num_tiles;
    win_sz = 1000;
    scale = win_sz / (num_tiles + 2);

    // Initialize Qt variables
    scene = new QGraphicsScene(0, 0, win_sz, win_sz);
    view = new World_view(scene, h_agent);
    view->resize(win_sz,win_sz);
    view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    init_map();
}

void Qt_world::init_map() {
    base_bg_sprite = new QPixmap("sprites/cobble.png");
    base_p_cobble_sprite = new QPixmap("sprites/p_cobble.png");
    base_wall_sprite = new QPixmap("sprites/wall.png");
    base_hero_sprite = new QPixmap("sprites/hero.png");
    base_wumpus_sprite = new QPixmap("sprites/wumpus2.png");
    base_p_wumpus_sprite = new QPixmap("sprites/p_wumpus2.png");
    base_stench_sprite = new QPixmap("sprites/stench3.png");
    base_pit_sprite = new QPixmap("sprites/pit.png");
    base_p_pit_sprite = new QPixmap("sprites/p_pit.png");
    base_breeze_sprite = new QPixmap("sprites/breeze.png");
    base_gold_sprite = new QPixmap("sprites/gold.png");
    base_fog_sprite = new QPixmap("sprites/fog.png");
    base_clear_sprite = new QPixmap("sprites/clear.png");
    base_not_clear_sprite = new QPixmap("sprites/not_clear.png");
    base_move_sprite = new QPixmap("sprites/move.png");

    // Initialize map between bits and sprites
    sprite_map[FOG] = base_fog_sprite;
    sprite_map[GOLD] = base_gold_sprite;
    sprite_map[WUMPUS] = base_wumpus_sprite;
    sprite_map[STENCH] = base_stench_sprite;
    sprite_map[PIT] = base_pit_sprite;
    sprite_map[POS_PIT] = base_p_pit_sprite;
    sprite_map[BREEZE] = base_breeze_sprite;
    sprite_map[WALL] = base_wall_sprite;
    sprite_map[EMPTY] = base_bg_sprite;
    sprite_map[POS_EMPTY] = base_p_cobble_sprite;
    sprite_map[POS_WUM] = base_p_wumpus_sprite;
    sprite_map[AGENT] = base_hero_sprite;
    sprite_map[IS_CLEAR] = base_clear_sprite;
    sprite_map[NOT_CLEAR] = base_not_clear_sprite;
    sprite_map[MOVE] = base_move_sprite;
    
    // Fill height map to know what elements to draw over
    height_map[FOG] = 1;
    height_map[GOLD] = 5;
    height_map[WUMPUS] = 5;
    height_map[STENCH] = 10;
    height_map[PIT] = 5;
    height_map[POS_PIT] = 2;
    height_map[BREEZE] = 9;
    height_map[WALL] = 10;
    height_map[EMPTY] = 4;
    height_map[POS_EMPTY] = 3;
    height_map[AGENT] = 6;
    height_map[POS_WUM] = 3;
    height_map[IS_CLEAR] = 10;
    height_map[NOT_CLEAR] = 10;
    height_map[MOVE] = 5;

    // Construct map between indices and screen position
    for (int i = 0; i < N + 2; i++) {
        vector<Point*> ind2win_row;
        for (int j = 0; j < N + 2; j++) {
            ind2win_row.push_back(new Point(i* scale, j * scale));
        }
        ind2win.push_back(ind2win_row);
    }
}

QGraphicsPixmapItem * Qt_world::set_tile(int x, int y, int elem_bits) {

    QGraphicsPixmapItem * tile;
    int base = 0x00000001;
    for (int i = 0; i < 32; i++) {
        int new_base = base << i;
        int single_elem_bits = new_base & elem_bits;

        if (single_elem_bits != 0) {
            int z = height_map[single_elem_bits];
            QPixmap * base_sprite = sprite_map[single_elem_bits];
            QPixmap * sprite = new QPixmap(base_sprite->scaled(scale, scale, Qt::KeepAspectRatio));
            tile = new QGraphicsPixmapItem(0, scene);
            tile->setPixmap(*sprite);
            tile->setPos(ind2win[x][y]->x, ind2win[x][y]->y);
            tile->setZValue(z);
            
        }

    }
    return tile;
}

void Qt_world::move_tile(QGraphicsPixmapItem * tile, int x, int y) {
    tile->setPos(ind2win[x][y]->x, ind2win[x][y]->y);
}

/**
 * The World View class exists to extend the QGraphicsView class. Its primary function
 * is to overwrite the keyPressEvents to provide input for human players
 * @param scene
 */
World_view::World_view(QGraphicsScene * scene, Logic_agent * h_agent) : QGraphicsView(scene) {
    agent = h_agent;
}

World_view::World_view(QGraphicsScene * scene) : QGraphicsView(scene) {
    agent = 0;
}

void World_view::keyPressEvent(QKeyEvent * e) {


    if (agent != 0) {
        switch (e->key()) {
//            case Qt::Key_A:
//                agent->make_move(WEST);
//                break;
//            case Qt::Key_S:
//                agent->make_move(NORTH);
//                break;
//            case Qt::Key_W:
//                agent->make_move(SOUTH);
//                break;
//            case Qt::Key_D:
//                agent->make_move(EAST);
//                break;
            case Qt::Key_Space:
                agent->make_move();
            default:
                std::cout << "invalid input" << std::endl;
        }
    }

    //    hero_tile->setPos(ind2win[p->x][p->y]->x, ind2win[p->x][p->y]->y);
    //        qApp->processEvents();

    QGraphicsView::keyPressEvent(e);
}

