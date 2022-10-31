//for convenience it has not been placed as a Board method
//@blocks is empty stack
//@level is currently achieved level
void generateLevel(stack<Block>& blocks, int level)
{
	//if u want do add level, change int maxLvl in Board.hpp and add sprite also in Board.hpp

	Block block("white");
	if (level == 1)
	{
		
			for (int i = 0; i < 5; i++)
			{
				
				blocks.push(block);//adding new block to stack
				blocks.top().setX(i * 120 + 130);//setting block location
				blocks.top().setY(80 + 290);
			}

		block.setType("green");
		blocks.push(block);
		blocks.top().setX(130);
		blocks.top().setY(120);
		blocks.push(block);
		blocks.top().setX(620);
		blocks.top().setY(120);

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
		blocks.top().setX(350);
		blocks.top().setY(400);
		blocks.push(block);
		blocks.top().setX(450);
		blocks.top().setY(400);
	}
	else if (level == 3)
	{
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
		blocks.top().setX(130);
		blocks.top().setY(370);
		blocks.push(block);
		blocks.top().setX(250);
		blocks.top().setY(370);
		blocks.push(block);
		blocks.top().setX(370);
		blocks.top().setY(370);
		blocks.push(block);
		blocks.top().setX(490);
		blocks.top().setY(370);
		blocks.push(block);
		blocks.top().setX(610);
		blocks.top().setY(370);
	}

}