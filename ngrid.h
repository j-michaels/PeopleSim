/*
 *  ngrid.h
 *  PeopleSim
 *
 *  Created by Joseph Michaels on 2/10/10.
 *  Copyright 2010 Eris Technologies, LLC. All rights reserved.
 *
 */

#import <vector>
#import "neuron.h"
#import "growth.h"
#define MAX_X		1000
#define MAX_Y		1000

/*
	하다
		Neuron growth
			implement commands
			'' runtime thingy
 
		Runtime for neurons
 
 */



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
	void grow(vector<ng_factor> *factors);
private:
	//grid_space grid[MAX_X][MAX_Y];
	//vector<grid_location> changed_spaces;
	vector<Neuron *> neurons;
	
	//vector<int> neur_inst;
};

