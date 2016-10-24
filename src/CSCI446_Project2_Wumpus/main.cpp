
/*
 * File:   main.cpp
 * Author: byrdie
 *
/ * Created on October 1, 2016, 3:48 PM
 */

#include "main.h"

int main(int argc, char *argv[]) {

            QApplication app(argc, argv);
    
            //1477267586
            init_rand();
        
            int N = 25;
            
            World * world = new World(N, 20, 20, 20);
            Engine * engine = new Engine(world);
            Reactive_agent * player = new Reactive_agent(engine, N, "../Test_run/test.txt");


    //    test_unification();

//    test_resolve();
//   test_linear_resolution();



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

void run_test(){
    string logic_file ="logic_results.txt";
    string reactive_file = "reactive_results.txt";
            
    
    int s_num_obs = 1;
    int num_obs = 3;
    
    int num_runs = 10;
    
    int size_step = 5;
    int num_steps = 5;
    
    int start = 5;
    
    for(int i = 1; i <= num_steps; i++){
        for(int j = 0; j < num_runs; j++){
            for(int k = 0; k < num_obs; k++){
                World * world = new World(i*size_step, s_num_obs + k, s_num_obs + k, s_num_obs + k);
                Engine * engine = new Engine(world);
                Logic_agent * l_agent = new Logic_agent(engine, i*size_step);
                engine = new Engine(world);
                Reactive_agent * r_agent = new Reactive_agent(engine, i*size_step, reactive_file);
            }
        }
    }
    
    
}

