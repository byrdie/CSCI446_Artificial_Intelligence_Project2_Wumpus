
#include <vector>

#include "world_gen.h"
#include "qt_world.h"

// Create a black world (world covered in fog of war)

World::World(int side_length, Logic_agent * agent) {

    N = side_length;
    qt_world = new Qt_world(N, agent);

    // Fill empty board with fog of war
    for (int i = 0; i < N + 2; i++) {
        vector<int> world_vec_row;
        for (int j = 0; j < N + 2; j++) {
            world_vec_row.push_back(FOG);
            qt_world->set_tile(i, j, FOG);
        }
        world_vec.push_back(world_vec_row);
    }

    qt_world->view->show();
}

World::World(int side_length, Human_agent * agent) {

    N = side_length;
    qt_world = new Qt_world(N, agent);

    // Fill empty board with fog of war
    for (int i = 0; i < N + 2; i++) {
        vector<int> world_vec_row;
        for (int j = 0; j < N + 2; j++) {
            world_vec_row.push_back(FOG);
            qt_world->set_tile(i, j, FOG);
        }
        world_vec.push_back(world_vec_row);
    }

    qt_world->view->show();
}

World::World(int side_length, Reactive_agent * agent) {

    N = side_length;
    qt_world = new Qt_world(N, agent);

    // Fill empty board with fog of war
    for (int i = 0; i < N + 2; i++) {
        vector<int> world_vec_row;
        for (int j = 0; j < N + 2; j++) {
            world_vec_row.push_back(FOG);
            qt_world->set_tile(i, j, FOG);
        }
        world_vec.push_back(world_vec_row);
    }

    qt_world->view->show();
}

// Create a master world with elements

World::World(int side_length, int n_wumpi, int n_pit, int n_barrier) {

    // Variable initialization
    N = side_length;
    num_wumpi = n_wumpi;
    num_pits = n_pit;
    num_barriers = n_barrier;

    qt_world = new Qt_world(N);

    // Fill empty board with empty squares and surround with walls
    for (int i = 0; i < N + 2; i++) {
        vector<int> world_vec_row;
        for (int j = 0; j < N + 2; j++) {
            if (i == 0 or i == N + 1 or j == 0 or j == N + 1) {
                world_vec_row.push_back(WALL);
                qt_world->set_tile(i, j, WALL);
            } else {
                world_vec_row.push_back(EMPTY);
                qt_world->set_tile(i, j, EMPTY);
            }

        }
        world_vec.push_back(world_vec_row);
    }

    //Place all the wumpi
    for (int i = 0; i < num_wumpi; i++) {
        Point * next_pt = add_element(WUMPUS);
        wumpus_list.push_back(next_pt);
        qt_world->set_tile(next_pt->x, next_pt->y, WUMPUS);
    }

    //Place all the pits
    for (int i = 0; i < num_pits; i++) {
        Point * next_pt = add_element(PIT);
        pit_list.push_back(next_pt);
        qt_world->set_tile(next_pt->x, next_pt->y, PIT);
    }

    // Place all the barriers
    for (int i = 0; i < num_barriers; i++) {
        Point * next_pt = add_element(WALL);
        barrier_list.push_back(next_pt);
        qt_world->set_tile(next_pt->x, next_pt->y, WALL);
    }

    // Place the gold
    Point * next_pt = add_element(GOLD);
    gold_list.push_back(next_pt);
    qt_world->set_tile(next_pt->x, next_pt->y, GOLD);

    //Place the stench
    for (int i = 0; i < num_wumpi; i++) {
        vector<Point *> affected_tiles = add_effect(wumpus_list[i], STENCH);
        for (uint j = 0; j < affected_tiles.size(); j++) {
            Point * tile = affected_tiles[j];
            qt_world->set_tile(tile->x, tile->y, STENCH);
        }
    }

    // Place the breeze
    for (int i = 0; i < num_pits; i++) {
        vector<Point *> affected_tiles = add_effect(pit_list[i], BREEZE);
        for (uint j = 0; j < affected_tiles.size(); j++) {
            Point * tile = affected_tiles[j];
            qt_world->set_tile(tile->x, tile->y, BREEZE);
        }
    }

    qt_world->view->show();

}

bool World::tile_is_empty(Point* p) {
    if (world_vec[p->x][p->y] == EMPTY) {
        return true;
    } else {
        return false;
    }
}

// Add specified element at random point

Point * World::add_element(int elem_bits) {

    while (true) {

        // Find a new random point
        int x = rand() % N + 1;
        int y = rand() % N + 1;
        Point * next_elem = new Point(x, y);

        // Check to see if that point is safe
        if (x == START_X and y == START_Y) {
            continue;
        } else if (tile_is_empty(next_elem) == false) {
            continue;
        } else {
            world_vec[x][y] = world_vec[x][y] | elem_bits;

            return new Point(x, y);
        }
    }
}

/**
 * Adds the desired effect about a point, taking care to not appy it to walls
 * @param 
 * @return 
 */
vector<Point *> World::add_effect(Point * center, int effect_bits) {

    // Construct a vector of the four points surrounding the center
    vector<Point *> neighbors = find_neighbors(center);
    vector<Point *> neighbors_copy = neighbors;

    //Loop through the neighbors and only apply effect if not wall
    for (int i = 0; i < 4; i++) {
        Point * pt = neighbors_copy[i];
        int tile = world_vec[pt->x][pt->y];
        if ((tile & WALL) == 0) {
            world_vec[pt->x][pt->y] = tile | effect_bits;
            qt_world->set_tile(pt->x, pt->y, effect_bits);
        } else {
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), pt), neighbors.end());
        }
    }

    return neighbors;

}

vector<Point *> World::find_neighbors(Point * center) {

    int cx = center->x;
    int cy = center->y;

    // Construct a vector of the four points surrounding the center
    vector<Point *> neighbors;
    neighbors.push_back(new Point(cx + 1, cy));
    neighbors.push_back(new Point(cx, cy + 1));
    neighbors.push_back(new Point(cx - 1, cy));
    neighbors.push_back(new Point(cx, cy - 1));

    return neighbors;

}
