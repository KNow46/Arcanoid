struct Speed
{
	float x;
	float y;
};
class Ball : public GameObject
{
private:
	Speed speed;
public:
	Ball()
	{
		width = 20;
		height = 20;
		position.x = canvasWidth / 2 + width / 2;
		position.y = canvasHeight - 100;
		speed.x = 0;
		speed.y = 0;
	}
	float getSpeedX()
	{
		return speed.x;
	}
	float getSpeedY()
	{
		return speed.y;
	}
	void setSpeedX(float x)
	{
		speed.x = x;
	}
	void setSpeedY(float y)
	{
		speed.y = y;
	}
	void moveX(float addX)
	{

		position.x += addX;
		//left ball-canvas reflection
		if (position.x < 20)
		{
			position.x = 23; //imperceptible teleport not to let ball stuck in the edge
			speed.x = -speed.x;
		}
		//right ball-canvas reflection
		if (position.x + width + 20 > canvasWidth)
		{
			position.x = canvasWidth - 23 - width;  //imperceptible teleport not to let ball stuck in the edge
			speed.x = -speed.x;
		}
	}
	void moveY(float addY)
	{
		position.y += addY;
		//up ball-canvas reflection
		if (position.y < 80)
		{
			position.y = 83;  //imperceptible teleport not to let ball stuck in the edge
			speed.y = -speed.y;
		}
	}

};