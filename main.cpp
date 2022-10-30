
#include <string>
#include "Framework.h"
#include <stack>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <stdlib.h> 
#include <cmath>

using namespace std;

//dimensions of canvas
const int canvasWidth = 800;
const int canvasHeight = 600;

#include "GameObject.hpp"
#include "Player.hpp"
#include "flyingBooster.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "generateLevel.hpp"

struct corner // one of eight points on ball used to collision with blocks
{
	string name;
	int x;
	int y;
};

struct activeBooster //size booster actually possesed by player
{
	string type;
	time_t end;
};

#include "Board.hpp"

int main(int argc, char* argv[])
{
	//run(new Board);
	return run(new Board);
}

