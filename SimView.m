//
//  SimView.m
//  PeopleSim
//
//  Created by Joseph Michaels on 3/13/09.
//  Copyright 2009 Eris Technologies, LLC. All rights reserved.
//

#import "SimView.h"
#import "wop.h"

@implementation SimView

@synthesize easygoingness, personality, personID;


- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
		srand(time(0));
		char *possibleHobbies_a[HOBBIES_SZ] = {"Knitting",
			"Baking cookies",
			"Playing Bingo",
			"Gardening",
			"Arranging furniture",
			"Dusting",
			"Flying kites",
		"Playing Scrabble"};
		possibleHobbies = possibleHobbies_a;
		world = MakeWorld(possibleHobbies);
		selectedPerson = NULL;
		_selectedPerson = NULL;
		iteration = 5;
		
		selectedPersonHobbies = [NSMutableArray array];
		_friends = [[NSMutableArray alloc] init];
    }
    return self;
}


- (NSMutableArray *)friends
{
	return _friends;
}

- (void)setFriends:(NSArray *)newFriends
{
	_friends = [NSMutableArray arrayWithArray:newFriends];
	
}

- (void)drawRect:(NSRect)rect {
    // Drawing code here.
	NSRect fillerRect = NSMakeRect(20, 20, 200.0, 200.0);
	[[NSColor whiteColor] set];
	NSRectFill(fillerRect);
	int i;
	for (i=0; i<N_PEOPLE; i++) {
		Person *p = world->people[i];
		if (p != NULL) {
			NSPoint origin = { p->coords.x*4 + 25, p->coords.y*4 + 25};
			
			NSRect rrect;
			rrect.origin = origin;
			rrect.size.width  = 2;
			rrect.size.height = 2;
			NSBezierPath *path;
			path = [NSBezierPath bezierPathWithRect:rrect];
			
			[path setLineWidth:2];
			
			[[NSColor whiteColor] set];
			[path fill];
			
			if ((p == _selectedPerson) && (p->partying == 1)) {
				[[NSColor purpleColor] set];
			} else if (p == _selectedPerson) {
				[[NSColor blueColor] set];
			} else if (p->partying == 1) {
				[[NSColor redColor] set];
			} else {
				[[NSColor grayColor] set];
			}
			[path stroke];
			
			if ((_selectedPerson != NULL) && ([checkBox state])) {
				LinkedListNode *pFriendNode = _selectedPerson->friends->head;
				while (pFriendNode != NULL) {
					Person *friend = (Person *)pFriendNode->data;
					//[path release];
					path = [NSBezierPath bezierPath];
					
					[path moveToPoint:NSMakePoint(_selectedPerson->coords.x*4 + 25, _selectedPerson->coords.y*4 + 25)];
					[path lineToPoint:NSMakePoint(friend->coords.x*4 + 25, friend->coords.y*4 + 25)];
					[[NSColor orangeColor] set];
					[path setLineWidth:0.5];
					[path stroke];
					pFriendNode = pFriendNode->next;
				}
				
			}
		}
	}
}

- (IBAction)runWorld:(id)sender {
	
	[self setNeedsDisplay: YES];
	[self updateHobbyList];
}

- (IBAction)iterate:(id)sender {
	iteration++;
	Iterate(world, 0);
	if (iteration % 7 == 0) {
		Party(world);
	}
	[self updateHobbyList];
	[self setNeedsDisplay: YES];
}

- (void)mouseDown:(NSEvent *)event {
	NSPoint event_location = [event locationInWindow];
	NSPoint local_point = [self convertPoint:event_location fromView:nil];
	int x, y;
	x = (local_point.x - 25) / 4;
	y = (local_point.y - 22) / 4;
	_selectedPerson = GetFirstAtWorldCoords(world, x, y);
	//if (_selectedPerson != NULL){
	//	NSString *str = [NSString stringWithFormat:@"%d", _selectedPerson->coords.x];
	//		[_mailboxes addObject:str];
	//}
	if (_selectedPerson != NULL) {
		personality = [NSString stringWithFormat:@"%d", _selectedPerson->personality];
		easygoingness = [NSString stringWithFormat:@"%d", _selectedPerson->easygoingness];
		personID = [NSString stringWithFormat:@"%d", _selectedPerson->id];
	}

	[self updateHobbyList];
	[self setNeedsDisplay: YES];
}

- (void)updateHobbyList {
	[selectedPersonHobbies removeObjectsInRange:NSMakeRange(0, [selectedPersonHobbies count])];
	[_friends removeObjectsInRange:NSMakeRange(0, [_friends count])];
	if (_selectedPerson != NULL) {
		int i;
		for (i=0; i<_selectedPerson->hobbies->size; i++) {
			char *hobby = (char *)GetInArray(_selectedPerson->hobbies, i);
			if (selectedPersonHobbies != NULL) {
			[selectedPersonHobbies addObject:[NSString stringWithCString:hobby]];
			}
		}
		LinkedListNode *friendNode = _selectedPerson->friends->head;
		while (friendNode != NULL) {
			Person *friend = (Person *)friendNode->data;
			NSString *str = [NSString stringWithFormat:@"%d", friend->id];
			[_friends addObject:str];
			friendNode = friendNode->next;
		}
	}
	[simViewController didChangeValueForKey:@"selection"];
}

- (NSMutableArray *)hobbies {
	return selectedPersonHobbies;
}

- (void)setHobbies:(NSArray *)newHobbies {
	selectedPersonHobbies = [NSMutableArray arrayWithArray:newHobbies];
}

- (int)iteration
{
	return iteration;
}

- (void)dealloc {
	NSLog(@"Deallocating world\n");
	FreeWorld(world);
	NSLog(@"Finished deallocating world\n");
	[super dealloc];
}

@end
