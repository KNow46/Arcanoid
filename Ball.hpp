class Ball : public GameObject
{
private:
	float speedX;
	float speedY;
public:
	Ball()
	{
		width = 20;
		height = 20;
		x = canvasWidth / 2 + width / 2;
		y = canvasHeight - 100;
		speedX = 0;
		speedY = 0;
	}
	float getSpeedX()
	{
		return speedX;
	}
	float getSpeedY()
	{
		return speedY;
	}
	void setSpeedX(float x)
	{
		speedX = x;
	}
	void setSpeedY(float y)
	{
		speedY = y;
	}
	void moveX(float speed)
	{

		x += speed;
		//left ball-canvas reflection
		if (x < 20)
		{
			x = 23; //imperceptible teleport not to let ball stuck in the edge
			speedX = -speedX;
		}
		//right ball-canvas reflection
		if (x + width + 20 > canvasWidth)
		{
			x = canvasWidth - 23 - width;  //imperceptible teleport not to let ball stuck in the edge
			speedX = -speedX;
		}
	}
	void moveY(float speed)
	{
		y += speed;
		//up ball-canvas reflection
		if (y < 80)
		{
			y = 83;  //imperceptible teleport not to let ball stuck in the edge
			speedY = -speedY;
		}
	}

};