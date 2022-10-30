//flying booster class
class Booster : public GameObject
{
private:
	float speed;//falling speed
	string type;//positive or negative 
public:
	Booster()
	{
		speed = 0.3;
		x = rand() % (canvasWidth - 40) + 20;
		if (rand() % 2 == 0)
			type = "negative";
		else
			type = "positive";
		height = 20;
		width = 60;
		y = 100;
	}
	void setSpeed(float sp)
	{

		speed = sp;
	}
	void setTypeRand()//set type of flying booster randomly
	{
		if (rand() % 2 == 0)
			type = "negative";
		else
			type = "positive";
	}
	void setXrand()
	{
		x = rand() % (canvasWidth - 40) + 20;
	}
	float getSpeed()
	{
		return speed;
	}
	string getType()
	{
		return type;
	}
	void move()
	{
		y += speed;
	}
};