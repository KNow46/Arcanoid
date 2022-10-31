struct Position
{
	float x;
	float y;
};

//basic class used to inheritance
class GameObject
{
protected:
	float width, height;
	Position position;
public:
	GameObject() :  width(10), height(10)
	{
		position.x = 0;
		position.y = 0;
	}
	void setX(float x)
	{
		position.x = x;
	}
	void setY(float y)
	{
		position.y = y;
	}
	void setWidth(float x)
	{
		width = x;
	}
	void setHeight(float y)
	{
		height = y;
	}
	float getX()
	{
		return position.x;
	}
	float getY()
	{
		return position.y;
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