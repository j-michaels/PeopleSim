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

/* 
 * Iterates through each square that has had its ion concentration changed,
 * propogating ions to adjacent squares
 */
void NGrid::iterate() {
	vector<grid_location>::iterator it;
	
	for (it = changed_spaces.begin(); it < changed_spaces.end(); it++) {
		//square changed : grid[it.x][it.y]
		int *num;
//		grid_location loc = make_loc(it.x, it.y);
		grid_location *locations = adjacent_squares(*it, num);
		
		
	}
	
	
}
