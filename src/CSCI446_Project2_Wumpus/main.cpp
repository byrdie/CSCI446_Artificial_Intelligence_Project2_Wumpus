
/*
 * File:   main.cpp
 * Author: byrdie
 *
/ * Created on October 1, 2016, 3:48 PM
 */

#include "main.h"

int main(int argc, char *argv[]) {

            QApplication app(argc, argv);
    
            init_rand();
        
            int N = 10;
            
            World * world = new World(N, 2, 2, 2);
            Engine * engine = new Engine(world);
            Logic_agent * player = new Logic_agent(engine, N);


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

