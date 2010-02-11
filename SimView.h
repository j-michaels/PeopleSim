//
//  SimView.h
//  PeopleSim
//
//  Created by Joseph Michaels on 3/13/09.
//  Copyright 2009 Eris Technologies, LLC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "wop.h"
#import "ETPerson.h"


@interface SimView : NSView {
	int iteration;
	World *world;
	ETPerson *selectedPerson;
	Person *_selectedPerson;
	char **possibleHobbies;
	IBOutlet NSTextField *hobbiesField;
	IBOutlet NSButton *checkBox;
	NSMutableArray *selectedPersonHobbies;
	IBOutlet NSObjectController *simViewController;
	IBOutlet NSArrayController *hobbiesController;
	IBOutlet NSArrayController *selectedPersonFriends;
	
	NSString *personality, *easygoingness, *personID;
	NSMutableArray *_friends;
}
- (NSMutableArray *)hobbies;
- (void)setHobbies:(NSArray *)newHobbies;
- (IBAction)runWorld:(id)sender;
- (IBAction)iterate:(id)sender;
- (void)updateHobbyList;
- (NSMutableArray *)friends;
- (void)setFriends:(NSArray *)newFriends;

@property(retain) NSString *easygoingness;
@property(retain) NSString *personality;
@property(retain) NSString *personID;

@end
