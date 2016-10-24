/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.h
 * Author: byrdie
 *
 * Created on October 2, 2016, 1:43 PM
 */

#ifndef MAIN_H
#define MAIN_H

#include "world_gen.h"
#include "qt_world.h"
#include "rule_parser.h"
#include "logic_agent.h"
#include "tests.h"
#include "reactive_agent.h"

using namespace std;

int main(int argc, char *argv[]);
void init_rand(unsigned long int seed);
void init_rand();
void run_test();



#endif /* MAIN_H */

