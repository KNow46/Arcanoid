//@blocks is stack of blocks declared in board class
//@level is currently achieved level
void generateLevel(stack<Block>& blocks, int level)
{
	if (level == 1)
	{
		Block block("green");
		for (int j = 0; j < 1; j++)
		{
			for (int i = 0; i < 5; i++)
			{

				blocks.push(block);//adding new block to stack
				blocks.top().setX(i * 120 + 130);//setting block location
				blocks.top().setY(j * 80 + 290);
			}
		}
		block.setType("gold");
		blocks.push(block);
		blocks.top().setX(30);
		blocks.top().setY(200);
		blocks.push(block);
		blocks.top().setX(720);
		blocks.top().setY(200);
	}
	else if (level == 2)
	{
		Block block("green");
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 5; i++)
			{

				blocks.push(block);
				blocks.top().setX(i * 120 + 130);
				blocks.top().setY(j * 80 + 130);
				if (j % 2 == 1)
					block.setType("green");//changing type of blocks witch will be generate
				else
					block.setType("white");
			}
		}
		block.setType("gold");
		blocks.push(block);
		blocks.top().setX(30);
		blocks.top().setY(200);
		blocks.push(block);
		blocks.top().setX(720);
		blocks.top().setY(200);
	}
	else if (level == 3)
	{
		Block block("green");
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 5; i++)
			{

				blocks.push(block);
				blocks.top().setX(i * 120 + 130);
				blocks.top().setY(j * 80 + 130);
				block.setType("green");

			}
		}
		block.setType("gold");
		blocks.push(block);
		blocks.top().setX(30);
		blocks.top().setY(200);
		blocks.push(block);
		blocks.top().setX(720);
		blocks.top().setY(200);
	}

}