//basic class used to inheritance
class GameObject
{
protected:
	float x, y, width, height;
public:
	GameObject() : x(10), y(10), width(10), height(10)
	{
		;
	}
	void setX(float X)
	{
		x = X;
	}
	void setY(float Y)
	{
		y = Y;
	}
	void setWidth(float WIDTH)
	{
		width = WIDTH;
	}
	void setHeight(float HEIGHT)
	{
		height = HEIGHT;
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	float getWidth()
	{
		return width;
	}
	float getHeight()
	{
		return height;
	}

};