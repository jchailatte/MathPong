#include "BlockMove.h"
#include <iostream>

BlockMove::BlockMove(class Actor* owner)
	:MoveComponent(owner)
{
	blockowner = owner;
	if (Random::GetIntRange(1, 10) > 5)
	{
		velocity.y = -velocity.y;
	}
	if (Random::GetIntRange(1, 10) > 5)
	{
		velocity.x = -velocity.x;
	}
}

void BlockMove::Update(float deltaTime)
{
	blockowner->SetPosition(Vector2(mOwner->GetPosition().x + velocity.x*deltaTime,		
		mOwner->GetPosition().y + velocity.y*deltaTime));

	if (blockowner->GetPosition().x <= 32+24 || blockowner->GetPosition().x >= 1024-32-24)
	{
		velocity.x = -velocity.x;
		if (blockowner->GetPosition().x <= 32+24)
		{
			blockowner->SetPosition(Vector2(32+24, blockowner->GetPosition().y));
		}
		if (blockowner->GetPosition().x >= 1024-32-24)
		{
			blockowner->SetPosition(Vector2(1024-32-24, blockowner->GetPosition().y));
		}
	}

	if (blockowner->GetPosition().y <= 32+24)
	{
		velocity.y = -velocity.y;
		blockowner->SetPosition(Vector2(blockowner->GetPosition().x, 32+24));
	}

	if (blockowner->GetPosition().y >= 770-24-32)
	{
		velocity.y = -velocity.y;
		blockowner->SetPosition(Vector2(blockowner->GetPosition().x, 770-32-24));
	}

	std::vector<Block*> allblocks = blockowner->GetGame()->GetBlocks();

	for (int i = 0; i < allblocks.size(); i++)
	{
		if (allblocks[i] == blockowner)
		{
			continue;
		}
		if (blockowner->GetCollision()->Intersect(allblocks[i]->GetCollision()))
		{
			Vector2 temp = Vector2(allblocks[i]->GetPosition().y - blockowner->GetPosition().y,
				allblocks[i]->GetPosition().x - blockowner->GetPosition().x);

			double degree = atan2(temp.x, temp.y) * 180 / Math::Pi;
			if (degree > 45 && degree < 135)
			{
				velocity.y = -velocity.y;
			}
			else if (degree < -45 && degree > -135)
			{
				velocity.y = -velocity.y;
			}
			else
			{
				velocity.x = -velocity.x;
			}
			break;
		}
	}
}