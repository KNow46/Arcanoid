enum bType
{
	negative = 0,
	positive = 1
};
//flying booster class
class Booster : public GameObject
{
private:
	float speed;//falling speed
	bType type;
public:
	Booster()
	{
		speed = 0.3;
		position.x = rand() % (canvasWidth - 40) + 20;
		if (rand() % 2 == 0)
			type = negative;
		else
			type = positive;
		height = 20;
		width = 60;
		position.y = 100;
	}
	void setSpeed(float sp)
	{

		speed = sp;
	}
	void setRandomType()//set type of flying booster randomly
	{
		if (rand() % 2 == 0)
			type = negative;
		else
			type = positive;
	}
	void setRandomX()
	{
		position.x = rand() % (canvasWidth - 40) + 20;
	}
	float getSpeed()
	{
		return speed;
	}
	bType getType()
	{
		return type;
	}
	void move()
	{
		position.y += speed;
	}
};