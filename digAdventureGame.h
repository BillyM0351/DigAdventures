/*
* Name: Billy Myers, 5004892732, Assignment 5
* Description: a brief description of the program.
* Input: Seed, Grid Height, Grid Length
* Output: a game where the player mines through a 2D grid full of rocks,
* treasure, armor, and carnivorous silverfish!
*/

#include "digAdventureObjects.h"
#include <string>

#define GAME_CONTINUE	0
#define GAME_EXIT_LOSE	1
#define GAME_EXIT_WIN	2
#define GAME_ERROR	   -1

class dig_adventure_game {
private:
	entity ***game_grid = nullptr;
	unsigned int game_width = 10;
	unsigned int game_height = 10;
	unsigned int difficulty = 1;
	miner *player = nullptr;

	void allocateGrid();
	void deallocateGrid();
	entity *allocateEntity(unsigned int);

	void populateGrid();

	void moveMiner(unsigned int nh, unsigned int nw);
public:
	dig_adventure_game(unsigned int, unsigned int, unsigned int);

	~dig_adventure_game();
	dig_adventure_game(const dig_adventure_game &copy);
	void operator=(const dig_adventure_game &copy);

	unsigned int playerMove();
	void playGame();
	void printGrid() const;
};
