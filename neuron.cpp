/*
 *  neuron.cpp
 *  PeopleSim
 *
 *  Created by Joseph Michaels on 2/20/10.
 *  Copyright 2010 Eris Technologies, LLC. All rights reserved.
 *
 */

#include "neuron.h"
#import "ngrid.h"

Neuron::Neuron(ncoord nloc, vector<ng_factor> *factors, void *grid) {
	loc = nloc;
	this->factors = (*factors);
	this->grid = grid;
}

void Neuron::spike() {
}

/* Run the grow commands */
void Neuron::grow() {
	vector<ng_factor>::iterator it;
	
	for (it = factors.begin(); it < factors.end(); it++) {
		switch (it->command) {
			case CONNECT_TO:
				Neuron *foo = (NGrid *)grid->neuron_from_ray(loc, it->orientation);
				connections.add(foo);
				break;
			case DIVIDE_TO:
				divide();
				break;
			default:
				break;
		}
	}
}

Neuron *Neuron::divide() {
	ncoord n_loc = ((NGrid *)grid)->request_new_loc(&loc);
	vector<ng_factor> ffactors = factors;
	vector<ng_factor>::iterator it;
	
	for (it = ffactors.begin(); it < ffactors.end(); it++) {
		switch (it->command) {
			case METHYLATE:
				ffactors.at(it->quantity).methylated = true;
				break;
			case UNMETHYLATE:
				ffactors.at(it->quantity).methylated = false;
				break;
		}
	}
	
	return new Neuron(n_loc, &ffactors, grid);
}