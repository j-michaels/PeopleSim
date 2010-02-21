/*
 *  neuron.h
 *  PeopleSim
 *
 *  Created by Joseph Michaels on 2/20/10.
 *  Copyright 2010 Eris Technologies, LLC. All rights reserved.
 *
 */

#import <vector>
#import "growth.h"

using namespace std;

typedef struct {
	int x, y, z;
} ncoord;

class Neuron {
public:
	Neuron(ncoord nloc, vector<ng_factor> *factors, void *grid);
	void grow();
	Neuron *divide();
	void spike();
private:
	void *grid;
	int bias, threshold, ion_concentration, size;
	ncoord loc;
	
	vector<ng_factor> factors;
	vector<void *> connections;
};