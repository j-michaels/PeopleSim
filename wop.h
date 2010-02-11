#include "array.h"
#include "linkedlist.h"

#define WORLD_SZ 40
#define ROW_SZ 4 + (WORLD_SZ * 7)
#define N_ADJ 8
#define N_PEOPLE 150
#define HOBBIES_SZ 8
#define RSVP_CHANCE 10
#define RSVP_CHANCE_INC 5

typedef enum {
    no, yes
} boolean;

/* Simple point struct */
typedef struct {
    int x, y;
} t_Point;

/* A person */
typedef struct Person {
    int easygoingness;
    int personality;
    int id;
    Array *hobbies;
    LinkedList *friends;
    t_Point coords;
    short partying;
} Person;

/* A world struct filled with pointers to Person structs */
typedef struct {
    /* a 2D array of pointers to a generic array. */
    Array *grid[WORLD_SZ][WORLD_SZ];
    /* an array of all people */
    Person *people[N_PEOPLE];
} World;


/* Allocate a person struct and initialize it
 * Parameters
 *      int id      A unique ID for the person
 *
 * Returns    An initialized Person struct
 */
Person *MakePerson(int id, char *hobby);

/* Move a Person to the specified coords of a World
 * Parameters
 *      World *w            The World object to find the Person in
 *      Person *person      The person to move
 *      Point *destination  The coordinates to move to
 * Returns
 *      void
 */
void MovePerson(World *w, Person *person, t_Point *destination);

/* Move a Person to the specified coords of a World
 * Parameters
 *      World *w            The World object to find the Person in
 *      Person *person      The person to move
 *      t_Point *destination  The coordinates to move to
 * Returns
 *      void
 */
void MovePersonToParty(World *w, Person *person, t_Point *destination);

/* Add a friend to a Person's friends list
 */
short PersonAddFriend(Person *person, Person *friend);

/* Ask a person to consider adopting a hobby. */
short PersonConsiderHobby(Person *person, char *hobby);

/* Get the group of people at the specified coords of a World
 * Parameters
 *      World *w        The World object to find the group in
 *      int x           The x coordinate to look at
 *      int y           The y coordinate to look at
 * Returns
 *      Array *        The group of people at the specified coordinates
 */
Array *GetAtWorldCoords(World *w, int x, int y);

/* Get the first Person at the specified coords of a world. */
Person *GetFirstAtWorldCoords(World *w, int x, int y);

/* Set a group at the specified coords of a World
 * Parameters
 *      World *w        The World object to set the group in
 *      int x           The x coordinate
 *      int y           The y coordinate
 *      Array *group    The group of people to set
 * Returns
 *      short           1 if successful, 0 if not
 */
short SetAtWorldCoords(World *w, int x, int y, Array *group);

/* Make a World struct and initialize its values.
 * Parameters
 *      char *possiblehobbies[]     An array of strings representing the name
 *                                  of each hobby. Must be HOBBIES_SZ in length.
 * Returns
 *      World *         the initialized World struct
 */
World *MakeWorld(char *possibleHobbies[]);

/* Free a person struct */
void FreePerson(Person *p);

/* Free a world struct */
void FreeWorld(World *w);

/* Compare two people to find out if they're compatible
 * Parameters
 *      Person *personA     One person to compare        
 *      Person *personB     Another person to compare
 * Returns
 *      short               1 if they're compatible, 0 if not
 */
short Compatible(Person *personA, Person *personB);

/* Make a Point struct
 * Parameters
 *      int x           The x coordinate
 *      int y           The y coordinate
 * Returns
 *      Point           The initialized Point struct
 */
t_Point MakePoint(int x, int y);

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
t_Point *FindAdjacents(World *w, int x, int y, int *num, boolean allowDiagonal);

/* Returns the same value as FindAdjacents() except without any empty locations. */
/* Filter the points returned by FindAdjacents()
 * Parameters - same as FindAdjacents(), plus
 *      int maxAtLoc        The maximum number of people at a location that is returned
 *                          Note that a value of zero returns coordinates to NULL pointers
 * Returns
 *      Point *             The filtered array of point structs
 */
t_Point *FindAdjacentPeople(World *w, int x, int y, int maxAtLoc, int *num, boolean allowDiagonal);

/* Iterate over all people in a World, first making friends with compatible
 * neighbors and then moving everyone randomly.
 * Parameters
 *      World *w        The world to iterate over
 * Returns
 *      short           0 always (may be changed to success/fail in the future)
 */
short Iterate(World *w, int iter);

/* Have several people throw parties
 * Parameters
 *      World *w        The world to throw parties in
 * Returns
 *      Array *         A report of what happened at all parties
 */
Array *Party(World *w);

/* Print a horizontal rule of ROW_SZ-1 in length */
void print_hr();

/* Print a World in grid form
 * Parameters
 *      World *w        The world to print
 * Returns
 *      void
 */
void PrintGrid(World *w);

/* Print each person with the IDs of their friends
 * Parameters
 *      World *w        The world to print
 * Returns
 *      void
 */
void PrintFriendsID(World *w);

/* Print out each line in a report
 * Parameters
 *      Array *report        The report to print
 * Returns
 *      void
 */
void PrintPartyReport(Array *report);