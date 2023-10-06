#include <iostream>
#include "digAdventureGame.h"
using namespace std;
int main()
{
cout << "Enter Seed: ";
int x;
cin >> x;
srand(x);
unsigned int h, w, s;
cout << "Enter Height of Game Grid (must be 10+): ";
cout << endl;
cin >> h;
cout << "Enter Width of Game Grid (must be 10+): ";
cout << endl;
cin >> w;
cout << "Enter the Difficulty Level (must be 1+): ";
cin >> s;
dig_adventure_game game(h, w, s);
game.playGame();
return 0;
}