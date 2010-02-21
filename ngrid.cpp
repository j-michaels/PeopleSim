/*
 *  ngrid.cpp
 *  PeopleSim
 *
 *  Created by Joseph Michaels on 2/10/10.
 *  Copyright 2010 Eris Technologies, LLC. All rights reserved.
 *
 */

#include "ngrid.h"

grid_location make_loc(int x, int y) {
	grid_location retloc;
	retloc.x = x;
	retloc.y = y;
	return retloc;
}

grid_location *adjacent_squares(grid_location loc, int *num) {
	grid_location *adjacents = (grid_location *)malloc(sizeof(grid_location) * 8);
	int x = loc.x;
	int y = loc.y;
	*num = 0;
    if (x > 0)
    {
        /* left adjacent exists */
        adjacents[*num] = make_loc(x-1, y);
        (*num)++;
        
        if (y > 0) {
            adjacents[*num] = make_loc(x-1, y-1);
            (*num)++;
        }
        if (y < MAX_Y-1) {
            adjacents[*num] = make_loc(x-1, y+1);
            (*num)++;
        }
    }
    if (x < MAX_X-1)
    {
        /* right adjacent exists */
        adjacents[*num] = make_loc(x+1, y);
        (*num)++;
        
        if (y > 0) {
            adjacents[*num] = make_loc(x+1, y-1);
            (*num)++;
        }
        if (y < MAX_Y-1) {
            adjacents[*num] = make_loc(x+1, y+1);
            (*num)++;
        }
	}
    if (y > 0)
    {
        adjacents[*num] = make_loc(x, y-1);
        (*num)++;
    }
    if (y < MAX_Y-1)
    {
        adjacents[*num] = make_loc(x, y+1);
        (*num)++;
    }
    
    return adjacents;
}

using namespace std;

NGrid::NGrid() {
	// do nothing
}

ncoord NGrid::request_new_loc(ncoord *loc) {
	ncoord coord;
	coord.x = 0;
	coord.y = 0;
	coord.z = 0;
	
	return coord;
}

/* */
Neuron *NGrid::neuron_from_ray(Neuron *n, int orientation) {
	// primary ray is _orientation_
	int theta = (orientation + 90) * PI/180;
	
	vector<Neuron *>::iterator it;
	
	for (it = neurons.begin(); it < neurons.end(); it++) {
		if (n != it) {
			// find the lower ray starting position
			ncoord lower_ray_ax_coord = make_coord(
				it->size * sin(theta),
				it->size * cos(theta));
		}
	}
}

/* Run the grow commands */
void NGrid::grow() {

}