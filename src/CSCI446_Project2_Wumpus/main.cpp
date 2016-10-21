
/*
 * File:   main.cpp
 * Author: byrdie
 *
/ * Created on October 1, 2016, 3:48 PM
 */

#include "main.h"

int main(int argc, char *argv[]) {

            QApplication app(argc, argv);
    
            init_rand( 1477040524);
        
            int N = 7;
            
            World * world = new World(N, 0, 4, 0);
            Engine * engine = new Engine(world);
            Human_agent * player = new Human_agent(engine, N);


    //    test_unification();

//    test_resolve();
//    test_linear_resolution();



           return app.exec();

}

/* Prepare random number generation */
void init_rand(unsigned long int seed) {
    srand(seed);
    printf("Seed: %lu\n", seed);
}

void init_rand() {
    unsigned int seed = time(NULL);
    srand(seed);
    printf("Seed: %u\n", seed);
}

