//
//  NeuroView.m
//  PeopleSim
//
//  Created by Joseph Michaels on 2/20/10.
//  Copyright 2010 Eris Technologies, LLC. All rights reserved.
//

#import "NeuroView.h"
#import "ngrid.h"
#import <vector>

@implementation NeuroView

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
		
		grid = new NGrid();
		Neuron *a, *b, *c, *d, *e;
		a = ((NGrid *)grid)->add_neuron(10, 10);
		b = ((NGrid *)grid)->add_neuron(40, 60);
		/*c = ((NGrid *)grid)->add_neuron(30, 100);
		d = ((NGrid *)grid)->add_neuron(200, 100);
		e = ((NGrid *)grid)->add_neuron(150, 90);
		*/
		NSLog(@"%d", b->loc.y);
//		vector<Neuron *> test;
		
		
		//a->test.push_back(b);
		a->connect_to(b);
//		b->connect_to(c);
    }
    return self;
}

- (void)drawRect:(NSRect)rect {
    // Drawing code here.
	NSRect fillerRect = NSMakeRect(20, 20, 200.0, 200.0);
	[[NSColor whiteColor] set];
	NSRectFill(fillerRect);
	
	vector<Neuron *>::iterator it;
	/*
	for (it = ((NGrid *)grid)->getNeurons()->begin(); it < ((NGrid *)grid)->getNeurons()->end(); it++) {
		NSBezierPath * path = [NSBezierPath bezierPath];
		[path setLineWidth:2];
		
		NSPoint center = { (*it)->loc.x, (*it)->loc.y };
		
		[path moveToPoint: center];
		[path appendBezierPathWithArcWithCenter: center
										 radius: (*it)->getSize()
									 startAngle: 0
									   endAngle: 360];
		
		[[NSColor whiteColor] set];
		[path fill];
		
		[[NSColor grayColor] set]; 
		[path stroke];
	}*/
}

@end
