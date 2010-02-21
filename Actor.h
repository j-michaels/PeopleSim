/*
 *  Actor.h
 *  PeopleSim
 *
 *  Created by Joseph Michaels on 2/10/10.
 *  Copyright 2010 Eris Technologies, LLC. All rights reserved.
 *
 */

#import <string>
#import "ngrid.h"

using namespace std;

class Actor {
public:
	Actor();
	void push_input(string *where);
private:
	
	NGrid *mind;
};