/* World of People
 * Joseph Michaels
 * Feb. 2009
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "wop.h"

/* Allocate a person struct and initialize it
 * Parameters
 *      int id      A unique ID for the person
 *
 * Returns    An initialized Person struct
 */
Person *MakePerson(int id, char *hobby)
{
    Person *pPerson = malloc(sizeof(Person));
    pPerson->easygoingness = rand() % 10;
    pPerson->personality = rand() % 10;
    pPerson->id = id;
    pPerson->hobbies = MakeArray();
    AddToArray(pPerson->hobbies, hobby);
    pPerson->friends = MakeLinkedList();
    pPerson->partying = 0;
    return pPerson;
}

/* Move a Person to the specified coords of a World
 * Parameters
 *      World *w            The World object to find the Person in
 *      Person *person      The person to move
 *      Point *destination  The coordinates to move to
 * Returns
 *      void
 */
void MovePerson(World *w, Person *person, t_Point *destination)
{
    /*printf("Moving person to (%d, %d).\n", destination->x, destination->y);*/
    
    if (GetAtWorldCoords(w, destination->x, destination->y) == NULL) {
        Array *group;
        Array *location = w->grid[person->coords.x][person->coords.y];
        
        if (location->size == 1) {
            /* */
            group = location;
            w->grid[person->coords.x][person->coords.y] = NULL;
        } else {
            /*
            PrintArray(location);*/
            RemoveFromArray(location, person);
            group = MakeArray();
            AddToArray(group, person);
        }
        person->coords.x = destination->x;
        person->coords.y = destination->y;
        person->partying = no;
        SetAtWorldCoords(w, destination->x, destination->y, group);
    }
}

/* Move a Person to the specified coords of a World
 * Parameters
 *      World *w            The World object to find the Person in
 *      Person *person      The person to move
 *      Point *destination  The coordinates to move to
 * Returns
 *      void
 */
void MovePersonToParty(World *w, Person *person, t_Point *destination)
{
    Array *destGroup = GetAtWorldCoords(w, destination->x, destination->y);
    if (destGroup != NULL) {
        Array *location = w->grid[person->coords.x][person->coords.y];
		if (location != NULL) {
			if (location->size == 1) {
				DestroyArray(location);
				w->grid[person->coords.x][person->coords.y] = NULL;
			} else {
				RemoveFromArray(location, person);
			}
		}
        person->coords.x = destination->x;
        person->coords.y = destination->y;
        /*SetAtWorldCoords(w, destination->x, destination->y, group);*/
        AddToArray(destGroup, person);
    }
}

/* Add a friend to a Person's friends list
 */
short PersonAddFriend(Person *person, Person *friend)
{
    return PushLinkedList(person->friends, friend);
}

/* Ask a person to consider adopting a hobby. */
short PersonConsiderHobby(Person *person, char *hobby)
{
    if (rand() % 100 > 40) {
        AddUniqueToArray(person->hobbies, hobby);
        return 1;
    }
    return 0;
}

/* Get the group of people at the specified coords of a World
 * Parameters
 *      World *w        The World object to find the group in
 *      int x           The x coordinate to look at
 *      int y           The y coordinate to look at
 * Returns
 *      Array *        The group of people at the specified coordinates
 */
Array *GetAtWorldCoords(World *w, int x, int y)
{
    if ((x < WORLD_SZ) && (y < WORLD_SZ)) {
        return w->grid[x][y];
    } else {
        return NULL;
    }
}

/* Get the first Person at the specified coords of a world. */
Person *GetFirstAtWorldCoords(World *w, int x, int y)
{
    Array *group = GetAtWorldCoords(w, x, y);
    if (group != NULL) {
        return (Person *)GetInArray(group, 0);
    } else {
        return NULL;
    }
}

/* Set a group at the specified coords of a World
 * Parameters
 *      World *w        The World object to set the group in
 *      int x           The x coordinate
 *      int y           The y coordinate
 *      Array *group    The group of people to set
 * Returns
 *      short           1 if successful, 0 if not
 */
short SetAtWorldCoords(World *w, int x, int y, Array *group)
{
    /* Check bounds and make sure nothing is already there. */
    if (((x < WORLD_SZ) && (y < WORLD_SZ)) && (w->grid[x][y] == NULL)) {
        w->grid[x][y] = group;
        /*person->coords = MakePoint(x, y);*/
        return 1;
    } else {
        return 0;
    }
}

/* Make a World struct and initialize its values.
 * Parameters
 *      char *possiblehobbies[]     An array of strings representing the name
 *                                  of each hobby. Must be HOBBIES_SZ in length.
 * Returns
 *      World *         the initialized World struct
 */
World *MakeWorld(char *possibleHobbies[])
{
    World *w = malloc(sizeof(World));
    int i,j;
    /* Initialize values to null */
    for (i=0; i<WORLD_SZ; i++) {
        for (j=0; j<WORLD_SZ; j++) {
            w->grid[i][j] = NULL;
        }
    }
    
    /* Make N_PEOPLE number of people */
    for (i=0; i<N_PEOPLE; i++) {
        /* Construct the person */
        char *hobby = possibleHobbies[rand() % HOBBIES_SZ];
        w->people[i] = MakePerson(i, hobby);
        int x, y;
        
        /* Find a random location within grid's bounds
         * This will result in an infinite loop if N_PEOPLE > WORLD_SZ*WORLD_SZ
         * Or if rand() doesn't visit every possible integer
         */
        do {
            x = rand() % WORLD_SZ;
            y = rand() % WORLD_SZ;
        } while (w->grid[x][y] != NULL);
        w->people[i]->coords = MakePoint(x, y);
        Array *a = MakeArray();
        AddToArray(a, w->people[i]);
        SetAtWorldCoords(w, x, y, a);
    }
    return w;
}

/* Free a person struct */
void FreePerson(Person *p)
{
    if (p != NULL)
    {
        FreeLinkedList(p->friends);
        DestroyArray(p->hobbies);
        free(p);
    }
}

/* Free a world struct */
void FreeWorld(World *w)
{
    if (w != NULL)
    {
        int i, j;
        for (i=0; i<N_PEOPLE; i++)
        {
            FreePerson(w->people[i]);
        }
        /* Dealloc all groups */
        for (i=0; i<WORLD_SZ; i++) {
            for (j=0; j<WORLD_SZ; j++) {
                if (w->grid[i][j] != NULL) {
                    DestroyArray(w->grid[i][j]);
                }
            }
        }
        
        free(w);
    }
}

/* Compare two people to find out if they're compatible
 * Parameters
 *      Person *personA     One person to compare        
 *      Person *personB     Another person to compare
 * Returns
 *      short               1 if they're compatible, 0 if not
 */
short Compatible(Person *personA, Person *personB)
{
    if ((personA->personality <= (personB->personality + personA->easygoingness)) &&
        (personA->personality >= (personB->personality - personA->easygoingness)) &&
        (personB->personality <= (personA->personality + personB->easygoingness)) &&
        (personB->personality >= (personA->personality - personB->easygoingness))) {
        return 1;
    } else {
        return 0;
    }
}

/* Make a Point struct
 * Parameters
 *      int x           The x coordinate
 *      int y           The y coordinate
 * Returns
 *      Point           The initialized Point struct
 */
t_Point MakePoint(int x, int y)
{
    t_Point p;
    p.x = x;
    p.y = y;
    return p;
}

/* Find all vertical, horizontal and optionally diagonal locations to the specified
 * coordinates in a World.
 * Parameters
 *      World *w                The world to iterate over
 *      int x                   The x coordinate
 *      int y                   The y coordinate
 *      int *num                The address of an integer to store the number of actual adjacents
 *      boolean allowDiagonal   Return squares that are diagonal to the specified coordinates
 * Returns
 *      Point *         An array of size N_ADJ of coordinates to adjacent squares
 */
t_Point *FindAdjacents(World *w, int x, int y, int *num, boolean allowDiagonal)
{
    t_Point *adjacents = malloc(sizeof(t_Point) * N_ADJ);
    *num = 0;
    if (x > 0)
    {
        /* left adjacent exists */
        adjacents[*num] = MakePoint(x-1, y);
        (*num)++;
        
        if (allowDiagonal) {
            if (y > 0) {
                adjacents[*num] = MakePoint(x-1, y-1);
                (*num)++;
            }
            if (y < WORLD_SZ-1) {
                adjacents[*num] = MakePoint(x-1, y+1);
                (*num)++;
            }
        }
    }
    if (x < WORLD_SZ-1)
    {
        /* right adjacent exists */
        adjacents[*num] = MakePoint(x+1, y);
        (*num)++;
        
        if (allowDiagonal) {
            if (y > 0) {
                adjacents[*num] = MakePoint(x+1, y-1);
                (*num)++;
            }
            if (y < WORLD_SZ-1) {
                adjacents[*num] = MakePoint(x+1, y+1);
                (*num)++;
            }
        }
    }
    if (y > 0)
    {
        adjacents[*num] = MakePoint(x, y-1);
        (*num)++;
    }
    if (y < WORLD_SZ-1)
    {
        adjacents[*num] = MakePoint(x, y+1);
        (*num)++;
    }
    
    return adjacents;
}

/* Returns the same value as FindAdjacents() except without any empty locations. */
/* Filter the points returned by FindAdjacents()
 * Parameters - same as FindAdjacents(), plus
 *      int maxAtLoc        The maximum number of people at a location that is returned
 *                          Note that a value of zero returns coordinates to NULL pointers
 * Returns
 *      Point *             The filtered array of point structs
 */
t_Point *FindAdjacentPeople(World *w, int x, int y, int maxAtLoc, int *num, boolean allowDiagonal)
{
    int totalAdjacent, i;
    *num = 0;
    t_Point *adjacentLocations = FindAdjacents(w, x, y, &totalAdjacent, allowDiagonal);
    t_Point *adjacentPeople = malloc(sizeof(t_Point) * N_ADJ);
    /* Find non nulls */
    for (i=0; i<totalAdjacent; i++)
    {
        Array *group = GetAtWorldCoords(w, adjacentLocations[i].x, adjacentLocations[i].y);
        if ((group != NULL) && (group->size <= maxAtLoc) && (maxAtLoc > 0))
        {
            adjacentPeople[*num] = adjacentLocations[i];
            (*num)++;
        }
        /* Empty squares */
        if ((group == NULL) && (maxAtLoc == 0))
        {
            adjacentPeople[*num] = adjacentLocations[i];
            (*num)++;
        }
    }
    free(adjacentLocations);
    return adjacentPeople;
}

/* Iterate over all people in a World, first making friends with compatible
 * neighbors and then moving everyone randomly.
 * Parameters
 *      World *w        The world to iterate over
 * Returns
 *      short           0 always (may be changed to success/fail in the future)
 */
short Iterate(World *w, int iter)
{
    int i, j, num_adjacent;
/*    printf("Iterating!!\n");
        printf("Not iter 8\n");*/
    for (i=0; i<N_PEOPLE; i++)
    {
        Person *person = w->people[i];
        
        if (person != NULL)
        {
            int n;
            t_Point *adjacentPeople = FindAdjacentPeople(w, person->coords.x, person->coords.y, N_PEOPLE, &num_adjacent, no);
            
            /* Look at each person adjacent */
            for (n=0; n<num_adjacent; n++)
            {
                Array *adjacentGroup = GetAtWorldCoords(w, adjacentPeople[n].x, adjacentPeople[n].y);
                Person *adjacentPerson;
                /*printf("Iterating group size: %d\n", adjacentGroup->size);*/
                for (j=0; j<adjacentGroup->size; j++) {
                    adjacentPerson = GetInArray(adjacentGroup, j);
                    /* Add the person as a friend if they are compatible. */
                    if (Compatible(adjacentPerson, person))
                    {
                        PersonAddFriend(person, adjacentPerson);
                    }
                }
            }
            free(adjacentPeople);
        }
    }
    
    
    /* move people randomly */
    for (i=0; i<N_PEOPLE; i++)
    {
        Person *person = w->people[i];
        /* Something went horribly wrong if person is NULL */
        if (person == NULL)
        {
            printf("UH OH\n");
        }
        /* Find all adjacent squares that are empty. */
        t_Point *adjacents = FindAdjacentPeople(w, person->coords.x, person->coords.y, 0, &num_adjacent, yes);
        if (num_adjacent > 0)
        {
            /* Select a random square of those available and move to it. */
            int r = rand() % num_adjacent;
            t_Point moveTo;
            moveTo.x = adjacents[r].x;
            moveTo.y = adjacents[r].y;
            MovePerson(w, person, &moveTo);
        }
        free(adjacents);
    }
    
    return 0;
}

/* Have several people throw parties
 * Parameters
 *      World *w        The world to throw parties in
 * Returns
 *      Array *         A report of what happened at all parties
 */
Array *Party(World *w)
{
    Array *report = MakeArray();
    /* Select 5 random people in the world and mark them as partying.
     * This will result in an infinite loop if N_PEOPLE < 5
     * or if rand() does not visit every possible value
     */
    Array *partyThrowers = MakeArray();
    while (partyThrowers->size < 5) {
        Person *person = w->people[rand() % N_PEOPLE];
        AddUniqueToArray(partyThrowers, person);
        person->partying = yes;
    }
    
    /* Iterate over all party throwers that have been selected.
     * This is done after they've been selected so that they're flagged
     * as partying, and thus won't be picked for teleportation.
     */
    int i, j, k;
    for (i=0; i<partyThrowers->size; i++) {
        Person *thrower = (Person *)GetInArray(partyThrowers, i);
        /* Select a random hobby for the party */
        char *partyActivity = GetInArray(thrower->hobbies, rand() % thrower->hobbies->size);
        /* Each party gets a section in the report. */
        char *partyHeader = malloc(sizeof(char) * 50);
        sprintf(partyHeader, "Person %d is throwing a %s party at (%d, %d).\n", thrower->id, partyActivity, thrower->coords.x, thrower->coords.y);
        AddToArray(report, partyHeader);
        
        /* Randomly teleport some friends. */
        LinkedListNode *friendNode = thrower->friends->head;
        /* Set the chance to 100% initially so at least 1 friend is attempted to teleport */
        int diceroll = 100;
        int chance = RSVP_CHANCE;
        while ((friendNode != NULL) && (diceroll > chance)) {
            Person *friend = (Person *)(friendNode->data);
            
            /* Only bring someone to a party if they aren't already at one. */
            if (friend->partying == no) {
                MovePersonToParty(w, friend, &(thrower->coords));

                friend->partying = yes;
                /* While at the party, the friend considers adopting the party's activity
                 * as a hobby. */
                char *reportString = malloc(sizeof(char) * 66);
                if (PersonConsiderHobby(friend, partyActivity)) {
                    /* Add this to the report. */
                    sprintf(reportString, "\tPerson %d attended the party and adopted the activity as a hobby.\n", friend->id);
                } else {
                    sprintf(reportString, "\tPerson %d attended the party.\n", friend->id);
                }
                AddToArray(report, reportString);
            }

            
            /* Roll the dice again and decrease the chance of selecting the next friend. */
            diceroll = rand() % 100;
            chance += RSVP_CHANCE_INC;
            
            /* Continue to the next friend. */
            friendNode = friendNode->next;
        }
        
        /* Add a newline to separate display of party reports */
        char *nl = malloc(sizeof(char) * 2);
        sprintf(nl, "\n");
        AddToArray(report, nl);
        
        /* All invitees become friends with each other if they are compatible. */
        Array *partyLocation = GetAtWorldCoords(w, thrower->coords.x, thrower->coords.y);
        for (j=1; j<partyLocation->size; j++) {
            for (k=1; k<partyLocation->size; k++) {
                Person *personA = GetInArray(partyLocation, j);
                Person *personB = GetInArray(partyLocation, k);
                if ((personA != personB) && (Compatible(personA, personB))) {
                    PersonAddFriend(personA, personB);
                }
            }
        }
    }
    DestroyArray(partyThrowers);
    return report;
}

/* Print a horizontal rule of ROW_SZ-1 in length */
void print_hr()
{
    int i;
    for (i=1; i<ROW_SZ; i++) {
        printf("-");
    }
    printf("\n");
}

/* Print a World in grid form
 * Parameters
 *      World *w        The world to print
 * Returns
 *      void
 */
void PrintGrid(World *w)
{
    int i,j;
    /* Header */
    printf("  |");
    for (i=0; i<WORLD_SZ; i++) {
        printf("  %2d  |", i);
    }
    printf("\n");
    /*printf("  |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |\n");*/
    print_hr();
    
    /* Iterator over each row */
    for (j=0; j<WORLD_SZ; j++) {
        /* Rows are constructed by two strings. */
        printf("%2d|", j);
        char s1[ROW_SZ];
        strcpy(s1, "");
        char s2[ROW_SZ];
        strcpy(s2, "  |");
        /* Iterator over each column. */
        for (i=0; i<WORLD_SZ; i++)
        {
            Array *a = GetAtWorldCoords(w, i, j);
            Person *p = GetInArray(a, 0);
            char s[8];
            if (p != NULL) {
                /* There's a person at this location, put its ID and number of friends into 
                   the output row strings. */
                if (a->size > 1) {
                    sprintf(s, " P %2d |", a->size);
                    strncat(s1, s, 8);
                    sprintf(s, "      |");
                    strncat(s2, s, 8);
                } else {
                    sprintf(s, " I %2d |", p->id);
                    strncat(s1, s, 8);
                    sprintf(s, " F %2d |", p->friends->size);
                    strncat(s2, s, 8);
                }
            } else {
                /* No person here, append filler whitespace to the output row strings. */
                sprintf(s, "      |");
                strncat(s1, s, 8);
                sprintf(s, "      |");
                strncat(s2, s, 8);
            }
        }
        printf("%70s\n%73s\n", s1, s2);
        print_hr();
    }
    /* Legend */
    printf("  |  LEGEND   I: Person ID  P: People at a party  F: Number of friends  |\n");
    print_hr();
}


/* Print each person with the IDs of their friends
 * Parameters
 *      World *w        The world to print
 * Returns
 *      void
 */
void PrintFriendsID(World *w)
{
    int i;
    /* Print the IDs of all the friends of each person. */
    printf("\nPerson ID\tFriends' IDs\n");
    for (i=0; i<N_PEOPLE; i++)
    {
        Person *p = w->people[i];
        if (p != NULL)
        {
            printf("%d\t\t", p->id);
            LinkedListNode *node = p->friends->head;
            if (node == NULL) {
                printf("No friends");
            } else {
                while (node != NULL) {
                    printf("%d", ((Person *)(node->data))->id);
                    if (node->next != NULL) {
                        printf(", ");
                    }
                    node = node->next;
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}

/* Print out each line in a report
 * Parameters
 *      Array *report        The report to print
 * Returns
 *      void
 */
void PrintPartyReport(Array *report)
{
    int i;
    for (i=0; i<report->size; i++) {
        printf((char *)GetInArray(report, i));
    }
}

/* Begin execution here */
/* int main()
{
	/* Grandmother appropriate hobbies */
	/*char *possibleHobbies[HOBBIES_SZ] = {"Knitting",
										"Baking cookies",
										"Playing Bingo",
										"Gardening",
										"Arranging furniture",
										"Dusting",
										"Flying kites",
										"Playing Scrabble"};
	
	/* Seed the random number generator with the current time. */
	/*srand(time(0));
	
	/* Make and initialize a World */
	/*World *pWorld = MakeWorld(possibleHobbies);
	
	int i;
	/* Print the World in its initial state. */
	/*printf("__Initial_________________________________________________________________\n");
	PrintGrid(pWorld);
	printf("\n");*/
	/* Iterate 25 times. */
	/* for (i=1; i<=25; i++)
	{
		Iterate(pWorld, i);
		
		/* Every 7 iterations, throw parties. */
		/*if (i % 7 == 0) {
			printf("__Party_%d_(iteration %2d)_________________________________________________\n", i / 7, i);
			Array *report = Party(pWorld);
			PrintGrid(pWorld);
			printf("\n");
			PrintPartyReport(report);
			printf("\n");
			DestroyArrayAndData(report);
		}
	} */
	
	/* Print the World at its last iteration. */
	/*printf("__Iteration_%2d___________________________________________________________\n", i-1);
	PrintGrid(pWorld);
	PrintFriendsID(pWorld);
	
	FreeWorld(pWorld);
} */