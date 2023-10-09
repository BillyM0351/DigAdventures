/*
A game where the player mines through a 2D grid full of rocks,
treasure, armor, and carnivorous silverfish!
*/

#include <iostream>
    using namespace std;

#define NOTHING     0
#define ROCK        1
#define SILVERFISH  2
#define ARMOR       3
#define TREASURE    4
#define WALL        5
#define EXIT        6 
#define MINER       7

/* empty_space and entity messages */
#define NOTH_MSG_DTSY "There is nothing here to dig..."
/* miner messages */
#define MINR_MSG_DSTY "The miner is attacked by Carnivorous Silverfish!"
#define MINR_MSG_DTOR "AAAAAAAGHHHHHHHHH!"
/* hardened_wall messages */
#define WALL_MSG_DTSY "The miner attempts to dig through the hardened wall. It cannot be destroyed."
/* rock messages */
#define ROCK_MSG_DTSY "The miner digs through some ordinary rock."
#define ROCK_MSG_DTOR "*crumbles*"
/* carnivorous_silverfish messages */
#define FISH_MSG_DTSY "The miner digs into rock invested with Carnivorous Silverfish!"
#define FISH_MSG_DTOR "*the silverfish hiss as they perish to the miner's spike armor*"
/* armor messages */
#define ARMR_MSG_DTSY "The miner digs up a component of the Spike Armor set!"
#define ARMR_MSG_DTOR "*the miner equips the spike armor*"
/* hidden_treasure messages */
#define TRSR_MSG_DTSY "The miner digs up some Hidden Treasure!"
#define TRSR_MSG_DTOR "*the miner stuffs shiny gems into their bag*"
/* exit messages */
#define EXIT_MSG_DTSY "The miner digs through the Exit!"
#define EXIT_MSG_DTOR "Congrats! You WIN!"

/*************************************
 * entity
*************************************/
class entity {
private:
    char shape;

protected:
    static bool display_messages;
    entity(char);

public:
    char getShape() const;
    virtual unsigned int destroy() const;
    virtual ~entity() = 0;
};

/*************************************
 * miner
*************************************/
class miner : public entity {
private:
    unsigned int spike_armor;
    int point_total;
    bool is_alive;
    unsigned int height;
    unsigned int width;

public:
    miner();
    miner(unsigned int, unsigned int);
    ~miner();
    unsigned int destroy();
    void givePoints(int);
    int getPoints() const;
    void armorUp();
    bool isStillAlive() const;
    void updateLocation(unsigned int, unsigned int);
    unsigned int getHeight() const;
    unsigned int getWidth() const;
    unsigned int getArmor() const;
};

/*************************************
 * empty_space
*************************************/
class empty_space : public entity {
public:
    empty_space();
};

/*************************************
 * hardened_wall
*************************************/
class hardened_wall : public entity {
public:
    hardened_wall();
    unsigned int destroy() const;
};

/*************************************
 * rock
*************************************/
class rock : public entity {
public:
    rock();
    ~rock();
    unsigned int destroy() const;
};

/*************************************
 * carnivorous_silverfish
*************************************/
class carnivorous_silverfish : public entity {
public:
    carnivorous_silverfish();
    ~carnivorous_silverfish();
    unsigned int destroy() const;
};

/*************************************
 * spike_armor
*************************************/
class spike_armor : public entity {
public:
    spike_armor();
    ~spike_armor();
    unsigned int destroy() const;
};

/*************************************
 * hidden_treasure
*************************************/
class hidden_treasure : public entity {
public:
    hidden_treasure();
    ~hidden_treasure();
    unsigned int destroy() const;
};

/*************************************
 * mine_exit
*************************************/
class mine_exit : public entity {
public:
    mine_exit();
    ~mine_exit();
    unsigned int destroy() const;
};
