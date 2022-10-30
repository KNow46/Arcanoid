//Player's racket class
class Player : public GameObject
{
private:
	int standardWidth;
public:
	Player()
	{
		width = 100;
		height = 25;
		x = canvasWidth / 2 + width / 2;
		y = canvasHeight - 50;
		standardWidth = width;
	}
	int getStandartWidth()
	{
		return standardWidth;
	}
};