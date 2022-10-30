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

//main game class responsible for most of the actions
class Board : public Framework
{

private:
	int goldBlocksAmount = 0;
	int collisionTime = 0; //used not to let the ball being reflected few times by rocket
	int boosterCollisionTime = 300; //used not to let booster being takenfew times
	int currentLevel = 1;
	//current position of mouse, updated in onMouseMove method
	int mouseX;
	int mouseY;

	Sprite* playerSprite[3]; //sprites used to animate player's rocket
	Sprite* ballSprite;
	Sprite* greenBlockSprite;
	Sprite* damagedGreenBlockSprite;
	Sprite* whiteBlockSprite;
	Sprite* goldBlockSprite;
	Sprite* backgroundSprite;
	Sprite* flyingBoosterSprite[2]; //two sprites, [0] positive size booster, [1] negative size booster
	 //sprites used to display boosters live time
	Sprite* boosterTimerSprite[2];
	Sprite* antyBoosterTimerSprite[2];

	Sprite* loseScreenSprite;
	Sprite* loseScreenHoveredSprite;

	bool loseScreenHovered = false;

	Player player; //player's rocket object

	Ball ball;

	stack <Block> blocks;

	time_t time1 = time(NULL);
	time_t time2 = time(NULL);

	stack<activeBooster> activeBoosters;//currently active boosters

	Booster flyingBooster;

	int rocketAniamtionCounter = 0;//enables racket animations

	bool lose = false;

	bool click = false;//false if any of mouse button is released

	float ballInitialSpeedX = -0.6;
	float ballInitialSpeedY = -0.8;
public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = canvasWidth;
		height = canvasHeight;
		fullscreen = false;
	}

	virtual bool Init()
	{
		generateLevel(blocks, 1);
		playerSprite[0] = createSprite("data\\50-Breakout-Tiles.png");
		setSpriteSize(playerSprite[0], player.getWidth(), player.getHeight());
		playerSprite[1] = createSprite("data\\51-Breakout-Tiles.png");
		setSpriteSize(playerSprite[1], player.getWidth(), player.getHeight());
		playerSprite[2] = createSprite("data\\52-Breakout-Tiles.png");
		setSpriteSize(playerSprite[2], player.getWidth(), player.getHeight());


		ballSprite = createSprite("data\\58-Breakout-Tiles.png");
		setSpriteSize(ballSprite, ball.getWidth(), ball.getHeight());

		flyingBoosterSprite[0] = createSprite("data\\booster.png");
		setSpriteSize(flyingBoosterSprite[0], flyingBooster.getWidth(), flyingBooster.getHeight());
		flyingBoosterSprite[1] = createSprite("data\\antyBooster.png");
		setSpriteSize(flyingBoosterSprite[1], flyingBooster.getWidth(), flyingBooster.getHeight());

		backgroundSprite = createSprite("data\\background.png");
		setSpriteSize(backgroundSprite, 800, 600);
		loseScreenSprite = createSprite("data\\loseScreen.png");
		setSpriteSize(backgroundSprite, 800, 600);
		loseScreenHoveredSprite = createSprite("data\\loseScreenHovered.png");
		setSpriteSize(backgroundSprite, 800, 600);

		antyBoosterTimerSprite[0] = createSprite("data\\antyBoosterTime.png");
		setSpriteSize(antyBoosterTimerSprite[0], 0, 21);
		boosterTimerSprite[0] = createSprite("data\\boosterTime.png");
		setSpriteSize(boosterTimerSprite[0], 0, 21);

		antyBoosterTimerSprite[1] = createSprite("data\\antyBoosterTime.png");
		setSpriteSize(antyBoosterTimerSprite[1], 0, 21);
		boosterTimerSprite[1] = createSprite("data\\boosterTime.png");
		setSpriteSize(boosterTimerSprite[1], 0, 21);

		greenBlockSprite = createSprite("data\\03-Breakout-Tiles.png");
		damagedGreenBlockSprite = createSprite("data\\04-Breakout-Tiles.png");
		whiteBlockSprite = createSprite("data\\17-Breakout-Tiles.png");
		goldBlockSprite = createSprite("data\\13-Breakout-Tiles.png");

		if (!blocks.empty())
		{
			setSpriteSize(greenBlockSprite, blocks.top().getWidth(), blocks.top().getHeight());
			setSpriteSize(damagedGreenBlockSprite, blocks.top().getWidth(), blocks.top().getHeight());
			setSpriteSize(whiteBlockSprite, blocks.top().getWidth(), blocks.top().getHeight());
			setSpriteSize(goldBlockSprite, blocks.top().getWidth(), blocks.top().getHeight());
		}
		ball.setSpeedY(ballInitialSpeedY);
		ball.setSpeedX(ballInitialSpeedX);

		time1 = time(NULL);
		time2 = time(NULL) - 15;
		ball.setX(400);
		ball.setY(500);
		return true;
	}

	virtual void Close()
	{

	}

	virtual bool Tick()
	{
		if (blocks.size() - goldBlocksAmount > 0 && lose == false)//true if game is in progress
		{
			//resetart flying booster every 15 seconds
			time2 = time(NULL) - 15;
			if (time2 >= time1)
			{
				time1 = time(NULL);
				flyingBooster.setXrand();
				flyingBooster.setY(100);
				flyingBooster.setTypeRand();
			}
			flyingBooster.move();

			//drawing some sprites
			drawSprite(backgroundSprite, 0, 0);

			drawSprite(antyBoosterTimerSprite[0], 154, 36);
			drawSprite(antyBoosterTimerSprite[1], 317, 36);
			drawSprite(boosterTimerSprite[0], 154, 36);
			drawSprite(boosterTimerSprite[1], 317, 36);

			setSpriteSize(antyBoosterTimerSprite[0], 0, 21);
			setSpriteSize(boosterTimerSprite[0], 0, 21);
			setSpriteSize(antyBoosterTimerSprite[1], 0, 21);
			setSpriteSize(boosterTimerSprite[1], 0, 21);

			drawSprite(ballSprite, ball.getX(), ball.getY());

			//drawing rocket animation
			int currsprite = 0;
			if (rocketAniamtionCounter >= 0 && rocketAniamtionCounter < 20)
				currsprite = 0;
			else if (rocketAniamtionCounter >= 20 && rocketAniamtionCounter < 40)
				currsprite = 1;
			else if (rocketAniamtionCounter >= 40 && rocketAniamtionCounter < 60)
				currsprite = 2;

			if (rocketAniamtionCounter > 60)
				rocketAniamtionCounter = 0;
			drawSprite(playerSprite[currsprite], player.getX(), player.getY());
			rocketAniamtionCounter++;

			if (!blocks.empty())
			{
				drawBlocks(blocks);
				ballBlocksCollision();
			}

			ballRocketCollision();


			if (flyingBooster.getType() == "positive")
			{
				drawSprite(flyingBoosterSprite[0], flyingBooster.getX(), flyingBooster.getY());
			}
			else if (flyingBooster.getType() == "negative")
			{
				drawSprite(flyingBoosterSprite[1], flyingBooster.getX(), flyingBooster.getY());
			}

			//areas which slows down or speeds up ball
			if (ball.getY() >= 382 && ball.getY() + ball.getHeight() <= 510)
			{
				ball.moveX(ball.getSpeedX() * 0.5);
				ball.moveY(ball.getSpeedY() * 0.5);
			}
			else if (ball.getY() >= 126 && ball.getY() + ball.getHeight() <= 254)
			{
				ball.moveX(ball.getSpeedX() * 1.5);
				ball.moveY(ball.getSpeedY() * 1.5);
			}
			else
			{
				ball.moveX(ball.getSpeedX());
				ball.moveY(ball.getSpeedY());
			}



			if (activeBoosters.size() < 2 && boosterCollisionTime > 300)
			{
				playerBoosterCollision();
			}
			if (!activeBoosters.empty())
			{
				workingBoosters();
			}
			setSpriteSize(playerSprite[0], player.getWidth(), player.getHeight());
			setSpriteSize(playerSprite[1], player.getWidth(), player.getHeight());
			setSpriteSize(playerSprite[2], player.getWidth(), player.getHeight());
			collisionTime++;
			boosterCollisionTime++;
			if (ball.getY() > canvasHeight)
			{
				lose = true;
			}
		}
		else if (lose == false)//next level setup
		{
			player.setWidth(player.getStandartWidth());
			currentLevel++;
			while (!activeBoosters.empty())
			{
				activeBoosters.pop();
			}
			while (!blocks.empty())
			{
				blocks.pop();
			}
			ball.setSpeedX(ballInitialSpeedX);
			ball.setSpeedY(ballInitialSpeedY);
			cout << 1;
			ball.setX(400);
			ball.setY(500);
			generateLevel(blocks, currentLevel);
		}
		else if (lose == true)//lose
		{
			player.setWidth(player.getStandartWidth());
			if (loseScreenHovered == false)
			{
				drawSprite(loseScreenSprite, 0, 0);
			}
			else
			{
				drawSprite(loseScreenHoveredSprite, 0, 0);

			}
		}
		if (mouseX > 152 && mouseX < 676 && mouseY > 254 && mouseY < 382)
		{
			loseScreenHovered = true;
			if (click == true && lose == true)//game restart
			{
				lose = false;
				while (!activeBoosters.empty())
				{
					activeBoosters.pop();
				}
				while (!blocks.empty())
				{
					blocks.pop();
				}
				ball.setSpeedX(ballInitialSpeedX);
				ball.setSpeedY(ballInitialSpeedY);
				cout << 2;
				ball.setX(400);
				ball.setY(500);

				generateLevel(blocks, currentLevel);

			}

		}
		else
		{
			loseScreenHovered = false;
		}


		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		mouseX = x;
		mouseY = y;
		player.setX(x - player.getWidth() / 2);
		//not to let rocket get out of canvas
		if (player.getX() < 20)
			player.setX(20);
		if (player.getX() + player.getWidth() > canvasWidth - 20)
			player.setX(canvasWidth - player.getWidth() - 20);
	}

	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
		if (isReleased == true)
		{
			click = false;
		}
		else
		{
			click = true;
		}
	}
	virtual void onKeyPressed(FRKey k)
	{
	}
	virtual void onKeyReleased(FRKey k)
	{
	}
private:
	void workingBoosters() //used to change rocket size if booster is active and display booster time
	{
		time_t currTime;
		currTime = time(NULL);
		int boosterGraphicTime = 0;
		float boostSize[10]; //array used for summary boost 
		for (int i = 0; i < 10; i++)
		{
			boostSize[i] = 1;
		}
		stack<activeBooster>newBoosterStack;
		player.setWidth(player.getStandartWidth()); //setting rocket's standard width
		int j = 0;
		while (!activeBoosters.empty())
		{
			boosterGraphicTime = activeBoosters.top().end - currTime;
			if (activeBoosters.top().end > currTime)//checking if booster is active
			{
				if (activeBoosters.top().type == "negative")
				{
					boostSize[j] = 0.6;//negative booster multiplier
					//changing sprite size depending on how much time is left
					if (j == 0)
					{
						setSpriteSize(antyBoosterTimerSprite[0], boosterGraphicTime * 71 / 20, 21);
						setSpriteSize(boosterTimerSprite[0], 0, 21);
					}
					else if (j == 1)
					{
						setSpriteSize(antyBoosterTimerSprite[1], boosterGraphicTime * 71 / 20, 21);
						setSpriteSize(boosterTimerSprite[1], 0, 21);
					}
				}
				else
				{
					boostSize[j] = 1.5;//positive booster multiplier
					//changing sprite size depending on how much time is left
					if (j == 0)
						if (j == 0)
						{
							setSpriteSize(antyBoosterTimerSprite[0], 0, 21);
							setSpriteSize(boosterTimerSprite[0], boosterGraphicTime * 71 / 20, 21);
						}
						else if (j == 1)
						{
							setSpriteSize(antyBoosterTimerSprite[1], 0, 21);
							setSpriteSize(boosterTimerSprite[1], boosterGraphicTime * 71 / 20, 21);
						}
				}
				newBoosterStack.push(activeBoosters.top());

			}
			j++;
			activeBoosters.pop();
		}
		int actualPlayerSize = player.getStandartWidth();
		//add up boosters
		for (int i = 0; i < 10; i++)
		{
			actualPlayerSize *= boostSize[i];
		}
		if (actualPlayerSize < 0.5 * player.getStandartWidth())
		{
			actualPlayerSize = 0.5 * player.getStandartWidth();//max negative boost
		}
		else if (actualPlayerSize > 2 * player.getStandartWidth())
		{
			actualPlayerSize = 2 * player.getStandartWidth();//max positive boost
		}
		//used to reverse newBooster stack
		stack<activeBooster> toReverseStack;
		while (!newBoosterStack.empty())
		{
			toReverseStack.push(newBoosterStack.top());
			newBoosterStack.pop();
		}
		activeBoosters = toReverseStack;//saving currently active boosters
		player.setWidth(actualPlayerSize);
	}
	void playerBoosterCollision()
	{
		if (flyingBooster.getX() + flyingBooster.getWidth() > player.getX() && flyingBooster.getX() < player.getX() + player.getWidth())
		{
			if (flyingBooster.getY() + flyingBooster.getHeight() >= player.getY() && flyingBooster.getY() <= player.getY() + player.getHeight())
			{
				activeBooster booster;
				booster.type = flyingBooster.getType();
				booster.end = time(NULL) + 20;
				activeBoosters.push(booster);
				boosterCollisionTime = 0;
				flyingBooster.setY(canvasHeight + 300);
			}
		}
	}
	void ballBlocksCollision()
	{
		stack<Block> newBlocksStack;
		int cornersCount = 8;
		corner ballCorners[8];//eight points on the ball
		ballCorners[0].name = "up-left";
		ballCorners[0].x = ball.getX() + ball.getWidth() * 1 / 6;
		ballCorners[0].y = ball.getY() + ball.getHeight() * 1 / 6;

		ballCorners[1].name = "up";
		ballCorners[1].x = ball.getX() + ball.getWidth() / 2;
		ballCorners[1].y = ball.getY();

		ballCorners[2].name = "up-right";
		ballCorners[2].x = ball.getX() + ball.getWidth() * 5 / 6;
		ballCorners[2].y = ball.getY() + ball.getHeight() * 1 / 6;

		ballCorners[3].name = "left";
		ballCorners[3].x = ball.getX();
		ballCorners[3].y = ball.getY() + ball.getHeight() / 2;

		ballCorners[4].name = "right";
		ballCorners[4].x = ball.getX() + ball.getWidth();
		ballCorners[4].y = ball.getY() + ball.getHeight() / 2;

		ballCorners[5].name = "bottom-left";
		ballCorners[5].x = ball.getX() + ball.getWidth() * 1 / 6;
		ballCorners[5].y = ball.getY() + ball.getHeight() * 5 / 6;

		ballCorners[6].name = "bottom";
		ballCorners[6].x = ball.getX() + ball.getWidth() / 2;
		ballCorners[6].y = ball.getY() + ball.getHeight();

		ballCorners[7].name = "bottom-right";
		ballCorners[7].x = ball.getX() + ball.getWidth() * 5 / 6;
		ballCorners[7].y = ball.getY() + ball.getHeight() * 5 / 6;


		while (!blocks.empty())
		{
			int cornerInside = -1;
			for (int i = 0; i < cornersCount; i++)//checking if corner is inside of block. cornerInside = -1 if it is not
			{
				if (ballCorners[i].x >= blocks.top().getX() && ballCorners[i].x <= blocks.top().getX() + blocks.top().getWidth())
				{
					if (ballCorners[i].y >= blocks.top().getY() && ballCorners[i].y <= blocks.top().getY() + blocks.top().getHeight())
					{
						cornerInside = i;
						break;
					}

				}
			}
			if (cornerInside != -1)
			{
				float safetyTeleport = 3;

				if (cornerInside == 0) //corner number 0 collision actitions
				{

					//"if" is used to checking which side is closer to corner which got into collision with block
					if (abs(ballCorners[0].x - (blocks.top().getX() + blocks.top().getWidth())) < abs(ballCorners[0].y - (blocks.top().getY() + blocks.top().getHeight())))
					{
						ball.setX(blocks.top().getX() + blocks.top().getWidth() + safetyTeleport);
						ball.setSpeedX(-ball.getSpeedX());
					}
					else
					{
						ball.setY(blocks.top().getY() + blocks.top().getHeight() + safetyTeleport);
						ball.setSpeedY(-ball.getSpeedY());
					}
				}
				if (cornerInside == 2)//corner number 2 collision actitions
				{

					if (abs(ballCorners[2].x - blocks.top().getX()) < abs(ballCorners[2].y - (blocks.top().getY() + blocks.top().getHeight())))
					{
						ball.setX(blocks.top().getX() - ball.getWidth() - safetyTeleport);
						ball.setSpeedX(-ball.getSpeedX());
					}
					else
					{
						ball.setY(blocks.top().getY() + blocks.top().getHeight() + safetyTeleport);
						ball.setSpeedY(-ball.getSpeedY());
					}
				}
				if (cornerInside == 5)
				{

					if (abs(ballCorners[5].x - (blocks.top().getX() + blocks.top().getWidth())) < abs(ballCorners[5].y - blocks.top().getY()))
					{
						ball.setX(blocks.top().getX() + blocks.top().getWidth() + safetyTeleport);
						ball.setSpeedX(-ball.getSpeedX());
					}
					else
					{
						ball.setY(blocks.top().getY() - ball.getHeight() - safetyTeleport);
						ball.setSpeedY(-ball.getSpeedY());
					}
				}
				if (cornerInside == 7)
				{

					if (abs(ballCorners[7].x - blocks.top().getX()) < abs(ballCorners[7].y - blocks.top().getY()))
					{
						ball.setX(blocks.top().getX() - ball.getWidth() - safetyTeleport);
						ball.setSpeedX(-ball.getSpeedX());
					}
					else
					{
						ball.setY(blocks.top().getY() - ball.getHeight() - safetyTeleport);
						ball.setSpeedY(-ball.getSpeedY());
					}
				}
				if (cornerInside == 1)
				{

					ball.setSpeedY(-ball.getSpeedY());
					ball.setY(blocks.top().getY() + blocks.top().getHeight() + safetyTeleport);
				}
				if (cornerInside == 3)
				{

					ball.setSpeedX(-ball.getSpeedX());
					ball.setX(blocks.top().getX() + blocks.top().getWidth() + safetyTeleport);
				}
				if (cornerInside == 4)
				{

					ball.setSpeedX(-ball.getSpeedX());
					ball.setX(blocks.top().getX() - ball.getWidth() - safetyTeleport);

				}
				if (cornerInside == 6)
				{

					ball.setSpeedY(-ball.getSpeedY());
					ball.setY(blocks.top().getY() - ball.getHeight() - safetyTeleport);
				}
				{
					blocks.top().getHit(); //hitting block
				}
			}
			if (blocks.top().getHp() > 0) //saving block if its hp is above 0
			{
				newBlocksStack.push(blocks.top());
			}
			blocks.pop();
		}
		blocks = newBlocksStack;
	}
	void ballRocketCollision()
	{
		if (collisionTime > 20)
		{
			if (ball.getY() + ball.getHeight() >= player.getY() && ball.getY() + ball.getHeight() <= player.getY() + ball.getHeight() * 0.4)
			{
				if (ball.getX() + ball.getWidth() * 0.7 > player.getX() && ball.getX() + ball.getWidth() * 0.3 < player.getX() + player.getWidth())
				{

					ball.setSpeedY(-ball.getSpeedY());
					collisionTime = 0;

				}
			}
		}
	}
	void drawBlocks(stack<Block>blocksCopy)
	{
		goldBlocksAmount = 0;
		while (!blocksCopy.empty())
		{
			if (blocksCopy.top().getType() == "green")
			{
				if (blocksCopy.top().getHp() == 2)
				{
					drawSprite(greenBlockSprite, blocksCopy.top().getX(), blocksCopy.top().getY());
				}
				else
				{
					drawSprite(damagedGreenBlockSprite, blocksCopy.top().getX(), blocksCopy.top().getY());
				}
			}
			if (blocksCopy.top().getType() == "gold")
			{
				drawSprite(goldBlockSprite, blocksCopy.top().getX(), blocksCopy.top().getY());
				goldBlocksAmount++;
			}
			if (blocksCopy.top().getType() == "white")
			{
				drawSprite(whiteBlockSprite, blocksCopy.top().getX(), blocksCopy.top().getY());
			}
			blocksCopy.pop();
		}
	}

};