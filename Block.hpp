class Block : public GameObject
{
private:
	string blockType; //for now "white"(1hp), "green"(2hp) or "gold" (indestructible)
	int hp;
public:
	Block(string btype) :blockType(btype)
	{
		x = 500;
		y = 200;
		height = 15;
		width = 50;
		hp = 1;
		if (blockType == "green")
		{
			hp = 2;
		}
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
	}
};