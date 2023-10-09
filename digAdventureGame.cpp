/*
A game where the player mines through a 2D grid full of rocks,
treasure, armor, and carnivorous silverfish!
*/

#include "digAdventureGame.h"

using namespace std;
/*******************************
 * Student Functions
*******************************/
/*
* function_identifier: This function allocates the 2d grid
* parameters: N/A
* return value: N/A
*/
void dig_adventure_game::allocateGrid() {

	// Check if game_grid contains memory
	if (game_grid != nullptr) {
		deallocateGrid();
	}

	// Allocate first two dimensions
	game_grid = new entity**[game_height];
	for (int i = 0; i < game_height; i++) {
		game_grid[i] = new entity*[game_width];
	}


	// Initialize each individual pointer to nullptr
	for (int i = 0; i < game_height; i ++) {
		for (int j = 0; j < game_width; j++) {
			game_grid[i][j] = nullptr;
		}
	}

}
/*
* function_identifier: function that deallocates the memory used for the game_grid
* parameters: N/A
* return value: N/A
*/
void dig_adventure_game::deallocateGrid() {

	//Check to see if game_grid is empty
	if (game_grid == NULL) {
		return;
	}

	//Deallocate dimensions in proper order
	for (int i = 0; i < game_height; i++) {
		for (int j = 0; j < game_width; j++) {
			delete game_grid[i][j];
		}
		delete[] game_grid[i];
	}

	//Delete game_grid and set to nullptr
	delete[] game_grid;
	game_grid = nullptr;


}
/*
* function_identifier: Helper function used to allocate different derived objects.
* parameters: Parameter passed in is returned to a pointer of a new object
* return value: N/A
*/
entity *dig_adventure_game::allocateEntity(unsigned int i) {

	//If the entity is nothing, return a new empty_space object
	if(i == NOTHING) {
		return (new empty_space());
	}
	//If the entity is a rock, return a new rock object
	if (i == ROCK) {
		return (new rock());
	}
	//If the entity is a carnivorous_silverfish, return a new carnivorous_silverfish object
	if (i == SILVERFISH) {
		return (new carnivorous_silverfish());
	}
	//If the entity is armor, return a new spiked_armor object
	if (i == ARMOR) {
		return (new spike_armor());
	}
	//If the entity is treasure, return a new treasure object
	if (i == TREASURE) {
		return (new hidden_treasure());
	}
	//If the entity is a wall, return a new wall object
	if (i == WALL) {
		return (new hardened_wall());
	}
	//If the entity is the exit, return a new exit object
	if (i == EXIT) {
		return (new mine_exit());
	}
	//If the entity is a player, return a Miner object
	if (i == MINER) {
		return (new miner());
	}

	//Else return nullptr
	return nullptr;
}

/*
* function_identifier: Function that moves the miner to a new location
* parameters: new height, new width
* return value: N/A
*/
void dig_adventure_game::moveMiner(unsigned int nh, unsigned int nw) {

	//Delete object that miner is trying to move to (parameters)
	delete game_grid[nh][nw];

	//Assign the player pointer to the new location in the grid
	game_grid[nh][nw] = player;

	//Overwrite teh miner's old location with a new empty_space object
	game_grid[player->getHeight()][player->getWidth()] = new empty_space;

	//Update the miner's height and width member variables
	player->updateLocation(nh,nw);
}

/*
* function_identifier: Function that prompts player where they would like to move
* parameters: N/A
* return value: unsigned integer returning value of object on the grid
*/
unsigned int dig_adventure_game::playerMove() {
	//Check to see if player is nullptr
	if (player == nullptr) {
		return GAME_ERROR;
	}
	//Prompt user to make a selection
	string selection;
	cout << "Where will the miner go?" << endl;
	cout << "(l)eft, (r)ight, (u)p, (d)own :" << endl;
	cin >> selection;
	while (true) {
		if (selection.length() >= 1) {
			if (selection[0] == 'l' || selection[0] == 'r' || selection[0] == 'u' || selection[0] == 'd') {
				break;
			}
		}
		cout << "Invalid entry!" << endl;
		cout << "(l)eft, (r)ight, (u)p, (d)own :" << endl;
		cin >> selection;
	}
	char direction = selection[0];

	//Computer where the miner will move and then destroy that location
	//after saving into result integer
	int new_h;
	int new_w;
	int result;

	switch (direction) {
		case 'l':
			new_h = player->getHeight();
			new_w = player->getWidth() - 1;
			result = game_grid[new_h][new_w]->destroy();
			break;
		case 'r':
			new_h = player->getHeight();
			new_w = player->getWidth() + 1;
			result = game_grid[new_h][new_w]->destroy();
			break;
		case 'u':
			new_h = player->getHeight() - 1;
			new_w = player->getWidth();
			result = game_grid[new_h][new_w]->destroy();
			break;
		case 'd':
			new_h = player->getHeight() + 1;
			new_w = player->getWidth();
			result = game_grid[new_h][new_w]->destroy();
			break;
	}

	//Move miner and return object at that location
	//If player lands on silverfish, deducts 5 points
	//If player lands on armor, adds one armor
	//If player lands on treasure, adds 3 points
	//If player lands on exit, player wins
	switch(result) {
		case NOTHING:
			moveMiner(new_h, new_w);
			return GAME_CONTINUE;
		case ROCK:
			moveMiner(new_h, new_w);
			player->givePoints(1);
			return GAME_CONTINUE;
		case SILVERFISH:
			player->destroy();
			player->givePoints(-5);

			//Check to see if player is still alive, if not game is over
			if (player->isStillAlive() == true) {
				moveMiner(new_h, new_w);
				return GAME_CONTINUE;
			}

			if (player->isStillAlive() == false) {
				game_grid[player->getHeight()][player->getWidth()] = nullptr;
				delete player;
				player = nullptr;
				return GAME_EXIT_LOSE;
			}
		case ARMOR:
			moveMiner(new_h, new_w);
			player->armorUp();
			return GAME_CONTINUE;
		case TREASURE:
			player->givePoints(3);
			moveMiner(new_h, new_w);
			return GAME_CONTINUE;
		case EXIT:
			moveMiner(new_h, new_w);
			return GAME_EXIT_WIN;
		case WALL:
			return GAME_CONTINUE;
	}

	return GAME_ERROR;
}

/*******************************
 * Mr. P Functions
*******************************/
void dig_adventure_game::populateGrid() {
	if(game_width < 2 || game_height < 2){
		return;
	}
	// Place the miner
	player = new miner(1, 1);
	game_grid[1][1] = player;
	/* Place the exit */
	game_grid[game_height - 2][game_width - 1] = allocateEntity(EXIT);
	/* Put up the walls */
	for (unsigned int h = 0; h < game_height; h++) {
		// Vertical Walls
		if(game_grid[h][0] == nullptr){
			game_grid[h][0] = allocateEntity(WALL);
		}
		if (h != (game_height - 2) && game_grid[h][game_width - 1] == nullptr) {
			game_grid[h][game_width - 1] = allocateEntity(WALL);
		}
	}
	for (unsigned int w = 0; w < game_width; w++) {
		// Horizontal Walls
		if(game_grid[0][w] == nullptr){
			game_grid[0][w] = allocateEntity(WALL);
		}
		if(game_grid[game_height - 1][w] == nullptr){
			game_grid[game_height - 1][w] = allocateEntity(WALL);
		}
	}
	/* Place the events */
	unsigned int sflh, sflw, htlh, htlw, salh, salw;
	unsigned int quadrant = 4;
	// Quadrant height
	for (unsigned int qh = 0; qh < quadrant / 2; qh++) {

		unsigned int startH, startW;
		startH = (qh * (game_height / 2));
		// Quadrant width
		for (unsigned int qw = 0; qw < quadrant / 2; qw++) {

			startW = (qw * (game_width / 2));
			// Add silverfish
			for (unsigned int d = 0; d < difficulty; d++) {
				
				do {
					sflh = startH + (rand() % (game_height / 2));
					sflw = startW + (rand() % (game_width / 2));
				} while (game_grid[sflh][sflw] != nullptr);
				game_grid[sflh][sflw] = allocateEntity(SILVERFISH);
				
			}
			// Add treasure
			do {
				htlh = startH + (rand() % (game_height / 2));
				htlw = startW + (rand() % (game_width / 2));
			} while (game_grid[htlh][htlw] != nullptr);
			game_grid[htlh][htlw] = allocateEntity(TREASURE);
			// add armor
			do {
				salh = startH + (rand() % (game_height / 2));
				salw = startW + (rand() % (game_width / 2));
			} while (game_grid[salh][salw] != nullptr);
			game_grid[salh][salw] = allocateEntity(ARMOR);
		}
	}
	/* Fill the rest with rock */
	for (unsigned int i = 0; i < game_height; i++) {
		for (unsigned int j = 0; j < game_width; j++) {
			if (game_grid[i][j] == nullptr) {
				game_grid[i][j] = allocateEntity(ROCK);
			}
		}
	}
}

dig_adventure_game::dig_adventure_game(unsigned int h, unsigned int w, unsigned int d) : game_height(h), game_width(w), difficulty(d){
	// Sanatize parameters
	if (w < 10) {
		game_width = 10;
	}
	if (h < 10) {
		game_height = 10;
	}

	if (d == 0) {
		d = 1;
	}
	else {
		unsigned int hd = d, wd = d;
		if (d > (((game_height - 2) / 2) - 1)) {
			hd = (((game_height - 2) / 2) - 1);
		}
		if (d > (((game_width - 2) / 2) - 1)) {
			wd = (((game_width - 2) / 2) - 1);
		}
		d = (wd < hd) ? wd : hd;
	}
	difficulty = d;
	// Allocate the grid
	allocateGrid();
	// Populate with objects
	populateGrid();
}

dig_adventure_game::~dig_adventure_game() {
	// Check to see if player still exists
	if (player != nullptr) {
		game_grid[player->getHeight()][player->getWidth()] = nullptr;
		delete player;
	}
	// Deallocate the grid
	deallocateGrid();	
}

void dig_adventure_game::playGame() {
	while (true) {
		// Print the game board
		printGrid();
		// Let the player move
		unsigned int rslt = playerMove();
		// If error
		if (rslt == GAME_ERROR) {
			cout << "An Error Ocurred. Please report this incident to yourself." << endl;
			return;
		}
		// If player loses or wins
		if (rslt == GAME_EXIT_LOSE || rslt == GAME_EXIT_WIN) {
			return;
		}
	}
}

void dig_adventure_game::printGrid() const {
	// Use a string so output happens all at once. 
	string output("");
	output += "\n";
	output += "------------------\n";
	output += string("| Current Score: |  ") + to_string(player->getPoints()) + string("\n");
	output += string("------------------\n");
	output += string(" * Armor Bonus: *  ") + to_string(player->getArmor()) + string("\n\n");
	for (unsigned int i = 0; i < game_height; i++) {
		for (unsigned int j = 0; j < game_width; j++) {
			if (game_grid[i][j] == nullptr) {
				// In case your grid contains nullptrs, you will question marks
				output += string("|?");
			}
			else {
				output += '|';
				output += game_grid[i][j]->getShape();
			}
		}
		output += "|\n";
	}
	output += '\n';
	cout << output;
}

// Copy ctor is here to prevent memory problems. 
// Does not make an identical copy
dig_adventure_game::dig_adventure_game(const dig_adventure_game &copy) {
	game_grid = nullptr; 
	player = nullptr;
	game_width = 0;
	game_height = 0;
	(*this) = copy;
}

// Operator= is here to prevent memory problems. 
// Does not make an identical copy
void dig_adventure_game::operator=(const dig_adventure_game &copy) {
	cout << "WARNING: You have called the Copy Ctor or Operator= for game object." << endl;
	cout << "A new game will be made instead because Mr.P was too lazy to do a deep copy." << endl;
	cout << "If you are a student who is still completing the assignment, you should not be seeing this message." << endl;
	deallocateGrid();
	if (player != nullptr) {
		delete player;
	}
	game_width = copy.game_width;
	game_height = copy.game_height;
	difficulty = copy.difficulty;
	allocateGrid();
	populateGrid();
}

