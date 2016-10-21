/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   typedef.h
 * Author: byrdie
 *
 * Created on October 1, 2016, 10:26 PM
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H

/* Define an integer representation of predicates*/
#define P_NEGATION      0x80000000      // predicate inversion
#define P_UNNEGATION    0x7FFFFFFF
#define P_BREEZY        0x00000001      // breezy predicate
#define P_PIT           0x00000002      // pit predicate
#define P_SAFE          0x00000004      // safe predicate
#define P_WALL          0x00000008
#define P_STINKY        0x00000010
#define P_WUMPUS        0x00000020
#define P_STENCH        0x00000040
#define P_BREEZE        0x00000080
#define P_EXPLORED      0x00000100
#define P_ISCLEAR       0x00000200
#define P_BESTMOVE      0x00000400
#define P_ADJEXPLORED   0x00000800

// Define Functions
// These must be larger than variables!
// Should all functions be invertible?
#define F_CONST         0x00008000      // Constant function
#define F_VAR           0x00010000      // Variable function
#define F_NORTH         0x00020000      // Returns the tile to the north
#define F_SOUTH         0x00040000      // Returns the tile to the south
#define F_EAST          0x00080000
#define F_WEST          0x00100000
#define F_RIGHT         0x00200000
#define F_LEFT          0x00400000
#define F_FORWARD       0x00400000
#define F_BACKWARD      0x00600000
/* How far to move for each cardinal function  */
#define DX              0x00010000
#define DY              0x00000001

// Define Argument types
#define A_CONST     0x80000000      // predicate inversion
#define A_UNCONST   0x7FFFFFFF                   
#define A_POINT     0x40000000


#define FOG     0x00000000
#define GOLD    0x00000001
#define WUMPUS  0x00000002
#define STENCH  0x00000004
#define PIT     0x00000008
#define BREEZE  0x00000080
#define WALL    0x00000010
#define EMPTY   0x00000020
#define AGENT   0x00000040
#define POS_PIT   0x00000100
#define POS_EMPTY 0x00000200

// Definite move types
#define EAST    0
#define NORTH   1
#define WEST    2
#define SOUTH   3

#include <vector>
#include <tuple>

using namespace std;

typedef vector<uint> func_args; // integer represents function parameters, variable index, or constant value
typedef tuple<uint, func_args> func; // integer represents function name, variable type, or constant type
typedef vector<func> pred_args; // Arguments to predicates
typedef tuple<uint, pred_args> pred; // Integer represents predicate name
typedef vector<pred> clause; // Clauses are ORs of predicates
typedef vector<clause> cnf; // CNF representation of all clauses
typedef vector<vector<cnf>> cnf2D; // 2D knowledge bases for neighborhood search

typedef uint pred_name; // Storage type for predicate names
typedef uint func_name; // Storage type for function names
typedef func pred_arg; // Storage type for arguments to a predicate
typedef uint func_arg; // Storage type for arguments to functions

typedef func_arg aconst; // Storage types for constants that are arguments to functions
typedef aconst apoint; // Storage types for constant coordinates in the wumpus world
typedef func_arg avar; // Storage type for variables that are arguments to functions

typedef vector<vector<func>> theta; // A list of substitutions

class Point {
public:
    int x;
    int y;;
    Point(float xpos, float ypos) {
        x = xpos;
        y = ypos;
    }
};

#endif /* TYPEDEF_H */

