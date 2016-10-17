/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: byrdie
 *
/ * Created on October 1, 2016, 3:48 PM
 */



#include "main.h"



int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
//    app.installEventFilter(new QApplicationFilter());
    
//    init_rand();
//
//    int N = 7;
//    
//    World * world = new World(N, 3, 3, 3);
//    Engine * engine = new Engine(world);
//    Human_agent * player = new Human_agent(engine, N);
    Knowledge * kb = new Knowledge();
    kb->print_kb();
    
    return app.exec();

}


/* Prepare random number generation */
void init_rand(unsigned long int seed) {
    srand(seed);
    printf("Seed: %u\n", seed);
}

void init_rand() {
    unsigned int seed = time(NULL);
    srand(seed);
    printf("Seed: %u\n", seed);
}