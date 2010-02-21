/*
 *  ngrid.h
 *  PeopleSim
 *
 *  Created by Joseph Michaels on 2/10/10.
 *  Copyright 2010 Eris Technologies, LLC. All rights reserved.
 *
 */

#import <vector>
#define MAX_X		1000
#define MAX_Y		1000

typedef struct {
	int material;
	int ion_concentration;
} grid_space;

typedef struct {
	int x,y;
} grid_location;

using namespace std;

class NGrid {
public:
	NGrid();
	void iterate();
	
private:
	grid_space grid[MAX_X][MAX_Y];
	vector<grid_location> changed_spaces;
	
	//vector<Neuron *> neurons;
	
	//vector<int> neur_inst;
};

