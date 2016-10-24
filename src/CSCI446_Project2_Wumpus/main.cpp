
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
    //run_test();
    int N = 5;

    World * world = new World(N, 1, 1, 0);
    Engine * engine = new Engine(world);
    Logic_agent * player = new Logic_agent(engine, N, "../Results/Logic_results.txt");


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

unsigned long int init_rand() {
    unsigned int seed = time(NULL);
    srand(seed);
    printf("Seed: %u\n", seed);
    return seed;
}

void run_test() {
    string logic_file = "../Results/Logic_results.txt";
    string reactive_file = "../Results/Reactive_results.txt";

    int s_num_obs = 3;
    int num_obs = 3;

    int num_runs = 3;

    int size_step = 5;
    int num_steps = 6;

    int start = 10;

    for (int i = 2; i <= num_steps; i++) {
        for (int j = 0; j < num_runs; j++) {
            for (int k = 0; k < num_obs; k++) {

                int seed = init_rand();
                World * world = new World(i*size_step, (s_num_obs * k), (s_num_obs * k), (s_num_obs * k));
                Engine * engine = new Engine(world);
                Logic_agent * l_agent = new Logic_agent(engine, i*size_step, logic_file);
                world->qt_world->view->close();
                delete world;
                delete engine;
                delete l_agent;


                init_rand(seed);
                world = new World(i*size_step, (s_num_obs * k), (s_num_obs * k), (s_num_obs * k));
                engine = new Engine(world);
                Reactive_agent * r_agent = new Reactive_agent(engine, i*size_step, reactive_file);
                world->qt_world->view->close();
                delete world;
                delete engine;
                delete r_agent;
            }
        }
    }


}

