//Player's racket class
class Player : public GameObject
{
private:
	int defaultWidth;
public:
	Player()
	{
		width = 100;
		height = 25;
		position.x = canvasWidth / 2 + width / 2;
		position.y = canvasHeight - 50;
		defaultWidth = width;
	}
	int getDefaultWidth()
	{
		return defaultWidth;
	}
};