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
	void connect_to(Neuron *other);
	int getSize();
	void spike();
	ncoord loc;
private:
	void *grid;
	int bias, threshold, ion_concentration, size;
	vector<ng_factor> factors;
	vector<Neuron *> connections;
};