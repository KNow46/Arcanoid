
#include <string>
#include "Framework.h"
#include <stack>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <stdlib.h> 
#include <cmath>
//#include <mmsystem.h>



using namespace std;
//dimensions of canvas
const int canvasWidth = 800;
const int canvasHeight = 600;

#include "GameObject.hpp"
#include "Player.hpp"
#include "Booster.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "generateLevel.hpp"
#include "Board.hpp"

int main(int argc, char* argv[])
{

	return run(new Board);
}

