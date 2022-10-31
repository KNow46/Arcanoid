class Block : public GameObject
{
private:
	string blockType; //for now "white"(1hp), "green"(2hp) or "gold" (indestructible)
	int hp;
public:
	Block(string bType)
	{
		position.x = 500;
		position.y = 200;
		height = 15;
		width = 50;

		setType(bType);
	}
	void getHit()
	{
		if (blockType != "gold")
			hp--;
	}
	int getHp()
	{
		return hp;
	}
	string getType()
	{
		return blockType;
	}
	void setType(string type)
	{
		blockType = type;
		if (blockType == "green")
		{
			hp = 2;
		}
		if (blockType == "white")
		{
			hp = 1;
		}
		if (blockType == "gold")
		{
			hp = 1;
		}
	}
};