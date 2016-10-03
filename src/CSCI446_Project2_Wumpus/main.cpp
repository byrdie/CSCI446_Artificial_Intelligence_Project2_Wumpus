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



#include "main.h"



int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
//    app.installEventFilter(new QApplicationFilter());
    
    init_rand();

    int N = 10;
    
    World * world = new World(N, 2, 1, 1);
    
    
    

    cout <<"here" << endl;
    
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