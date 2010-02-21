/*
 *  growth.h
 *  PeopleSim
 *
 *  Created by Joseph Michaels on 2/20/10.
 *  Copyright 2010 Eris Technologies, LLC. All rights reserved.
 *
 */

/* Commands for neuron growth
 effectively the Actor's DNA */
typedef enum {
	DIVIDE_TO = 1,
	CONNECT_TO = 2,
	METHYLATE = 3,
	UNMETHYLATE = 4
} neurogrowth_command;

typedef struct {
	neurogrowth_command command;
	int quantity;
	int orientation;
	bool methylated;
} ng_factor;