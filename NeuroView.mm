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
    }
    return self;
}

- (void)drawRect:(NSRect)rect {
    // Drawing code here.
	NSRect fillerRect = NSMakeRect(20, 20, 200.0, 200.0);
	[[NSColor whiteColor] set];
	NSRectFill(fillerRect);
	
	vector<Neuron *>::iterator it;
	
	for (it = grid->getNeurons().begin(); it < grid.getNeurons().end(); it++) {
		NSBezierPath * path = [NSBezierPath bezierPath];
		[path setLineWidth:4];
		
		NSPoint center = { 128,128 };
		
		[path moveToPoint: center];
		[path appendBezierPathWithArcWithCenter: center
										 radius: 64
									 startAngle: 0
									   endAngle: 321];
		
		[[NSColor whiteColor] set];
		[path fill];
		
		[[NSColor grayColor] set]; 
		[path stroke];
	}
}

@end
