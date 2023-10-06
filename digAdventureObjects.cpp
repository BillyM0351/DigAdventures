/*
* Name: Billy Myers, 5004892732, Assignment 5
* Description: a brief description of the program.
* Input: Seed, Grid Height, Grid Length
* Output: a game where the player mines through a 2D grid full of rocks,
* treasure, armor, and carnivorous silverfish!
*/

#include "digAdventureObjects.h"
using namespace std;

/*************************************
 * entity function definitions
*************************************/
// Initialize display_messages to true
bool entity::display_messages = true;

//Initializes shape of the object
entity::entity(char s) {
    shape = s;
}

//pure virtual destructor
entity::~entity() {}

//getter function for entity shape
char entity::getShape() const{
    return shape;
}

//Virtual function that returns nothing
unsigned int entity::destroy() const {
    cout << NOTH_MSG_DTSY;
    return NOTHING;
}



/*************************************
 * miner function definitions
*************************************/
//Default constructor
miner::miner():entity('M') {
    spike_armor = 0;
    point_total = 0;
    is_alive = true;
    height = 1;
    width = 1;
}

//Parameter constructor that places the miner at specified coordinates
miner::miner(unsigned int h, unsigned int w):entity('M') {
    spike_armor = 0;
    point_total = 0;
    is_alive = true;
    height = h;
    width = w;
}

//Miner destructor. Prints MINR_MSG_DTOR and sets display messages to false
miner::~miner() {
    if(display_messages == true) {
        cout << MINR_MSG_DTOR;
        display_messages = false;
    }
}

//Called if silverfish attacks the player. Checks for armor, if none
//the player dies.
unsigned int miner::destroy() {
    cout << MINR_MSG_DSTY;

    if(spike_armor == 0) {
        is_alive = false;
    }
    else {
        spike_armor = spike_armor - 1;
    }

    return MINER;
}

//Adds points to the point_total
void miner::givePoints(int p) {
    point_total = p + point_total;
}

//Getter function for the point_total
int miner::getPoints() const {
    return point_total;
}

//Increases spike_armor count
void miner::armorUp() {
    spike_armor = spike_armor + 1;
}

//getter function for is_alive variable
bool miner::isStillAlive() const {
    return is_alive;
}

//updates miner location at coordinates passed in parameter
void miner::updateLocation(unsigned int h, unsigned int w) {
    height = h;
    width = w;
}

//Getter function to return height value
unsigned int miner::getHeight() const {
    return height;
}

//Getter function to return width value
unsigned int miner::getWidth() const {
    return width;
}

//Getter function to return armor count
unsigned int miner::getArmor() const {
    return spike_armor;
}



/*************************************
 * empty_space function definitions
*************************************/
//Empty_space constructor that initliazes shape to ' '
empty_space::empty_space():entity(' ') {}

/*************************************
 * hardened_wall function definitions
*************************************/
//hardened_wall constructor that initliazes shape to '#'
hardened_wall::hardened_wall():entity('#') {}

//destroy hardened_wall object and print destroy message
unsigned int hardened_wall::destroy() const {
    cout << WALL_MSG_DTSY;
    return WALL;
}


/*************************************
 * rock function definitions
*************************************/
//rock constructor that initliazes shape to '0'
rock::rock():entity('0') {}

//rock destructor
rock::~rock() {
    if (display_messages == true) {
        cout << ROCK_MSG_DTOR;
    }
}

//destroy hardened_wall object and print destroy message
unsigned int rock::destroy() const {
    cout << ROCK_MSG_DTSY;
    return ROCK;
}

/*************************************
 * carnivorous_silverfish function definitions
*************************************/
//carnivorous_silverfish constructor that initliazes shape to '0'
carnivorous_silverfish::carnivorous_silverfish():entity('0') {}

//carnivorous_silverfish destructor
carnivorous_silverfish::~carnivorous_silverfish() {
    if (display_messages == true) {
        cout << FISH_MSG_DTOR;
    }
}

//destroy carnivorous_silverfish object and print destroy message
    unsigned int carnivorous_silverfish::destroy() const {
        cout << FISH_MSG_DTSY;
        return SILVERFISH;
    }


/*************************************
 * spike_armor function definitions
*************************************/
//spike_armor constructor that initliazes shape to '^'
spike_armor::spike_armor():entity('^') {}

//spike_armor destructor
spike_armor::~spike_armor() {
    if (display_messages == true) {
        cout << ARMR_MSG_DTOR;
    }
}

//destroy spike_armor object and print destroy message
unsigned int spike_armor::destroy() const {
    cout << ARMR_MSG_DTSY;
    return ARMOR;
}

/*************************************
 * hidden_treasure function definitions
*************************************/
//hidden_treasure constructor that initliazes shape to '$'
hidden_treasure::hidden_treasure():entity('$') {}

//hidden_treasure destructor
hidden_treasure::~hidden_treasure() {
    if (display_messages == true) {
        cout << TRSR_MSG_DTOR;
    }
}

//destroy spike_armor object and print destroy message
unsigned int hidden_treasure::destroy() const {
    cout << TRSR_MSG_DTSY;
    return TREASURE;
}

/*************************************
 * mine_exit function definitions
*************************************/
//mine_exit constructor that initliazes shape to 'E'
mine_exit::mine_exit():entity('E') {}

//mine_exit destructor
mine_exit::~mine_exit() {
    if (display_messages == true) {
        cout << EXIT_MSG_DTOR;
        display_messages = false;
    }
}

//destroy mine_exit object and print destroy message
unsigned int mine_exit::destroy() const {
    cout << EXIT_MSG_DTSY;
    return EXIT;
}
