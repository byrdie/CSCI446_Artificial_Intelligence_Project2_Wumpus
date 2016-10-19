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
        //app.installEventFilter(new QApplicationFilter());

        init_rand();
    
        int N = 7;
        
        World * world = new World(N, 3, 3, 3);
        Engine * engine = new Engine(world);
        Human_agent * player = new Human_agent(engine, N);
//    Knowledge * kb = new Knowledge();
//
//    for (uint i = 0; i < kb->static_kb.size() / 2; i++) {
//        pred p1 = kb->static_kb[2 * i][0];
//        pred p2 = kb->static_kb[2 * i + 1][0];
//
//
//        
//        kb->print_pred(p1);
//        cout << endl;
//        kb->print_pred(p2);
//        cout << endl;
//        cout << endl;
//        theta sub_list;
//        sub_list = kb->unification(p1, p2, sub_list);
//
//        cout << "num subs: " << sub_list.size() << endl;
//
//        for (uint j = 0; j < sub_list.size(); j++) {
//            kb->print_pred_args(sub_list[j]);
//            cout << endl;
//
//            p1 = kb->apply_sub_to_pred(p1, sub_list[j]);
//            p2 = kb->apply_sub_to_pred(p2, sub_list[j]);
//
//        }
//        cout << endl;
//        kb->print_pred(p1);
//        cout << endl;
//        kb->print_pred(p2);
//        cout << endl;
//        cout << "----------------------" << endl;
//    }




    //    cnf resolvents = kb->resolve(c1,c2);

    //    kb->print_kb(resolvents);

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
