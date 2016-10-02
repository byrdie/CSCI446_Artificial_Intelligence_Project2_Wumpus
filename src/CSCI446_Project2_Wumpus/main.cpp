/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: byrdie
 *
 * Created on October 1, 2016, 3:48 PM
 */



#include "qt_world.h"

using namespace std;
//using namespace Qt;





int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
//    app.installEventFilter(new QApplicationFilter());

    int N = 10;
    int win_sz = 500;
    
    QGraphicsScene *scene = new QGraphicsScene(0, 0, win_sz, win_sz);
    Qt_world * gameboard = new Qt_world(scene, N, win_sz);
    gameboard->show();

    cout <<"here" << endl;
    
    return app.exec();

}