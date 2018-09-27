#include "BallMove.h"

#include <iostream>
#include <string>

BallMove::BallMove(class Actor* owner)
	:MoveComponent(owner)
{
	ballowner = owner;
	collision = false;
}

void BallMove::Update(float deltaTime)
{
	MoveComponent::Update(deltaTime);
	


	ballowner->SetPosition(Vector2(mOwner->GetPosition().x + velocity.x*deltaTime,		//removed getfoward
		mOwner->GetPosition().y + velocity.y*deltaTime));

	if (ballowner->GetPosition().x <= 32 + 10 || ballowner->GetPosition().x >= 1024 - 32 - 10)
	{
		velocity.x = -velocity.x;
		if (ballowner->GetPosition().x <= 32 + 10)
		{
			ballowner->SetPosition(Vector2(32 + 10, ballowner->GetPosition().y));
		}
		if (ballowner->GetPosition().x >= 1024 - 32 - 10)
		{
			ballowner->SetPosition(Vector2(1024 - 32 - 10, ballowner->GetPosition().y));
		}
	}

	if (ballowner->GetPosition().y <= 32 + 10)
	{
		velocity.y = -velocity.y;
		ballowner->SetPosition(Vector2(ballowner->GetPosition().x, 32 + 10));
	}

	if (ballowner->GetPosition().y >= 770 - 32 - 10)
	{
		velocity.y = -velocity.y;
		ballowner->SetPosition(Vector2(ballowner->GetPosition().x, 770 - 32 - 10));
	}

	std::vector<Block*> allblocks = ballowner->GetGame()->GetBlocks();

	for (int i = 0; i < allblocks.size(); i++)
	{
		if (ballowner->GetCollision()->Intersect(allblocks[i]->GetCollision()))
		{
			Vector2 temp = Vector2(allblocks[i]->GetPosition().y - ballowner->GetPosition().y,
				allblocks[i]->GetPosition().x - ballowner->GetPosition().x);

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
			std::string b = allblocks[i]->value;

			if (ballowner->GetGame()->GetSolution() == allblocks[i]->value)
			{
				allblocks[i]->SetPosition(Random::GetVector(Vector2(32 + 24, 32 + 24), Vector2(1024 - 24 - 32, 770 - 32 + 24)));
				ballowner->GetGame()->ReLoadNumbers(i);
			}
			else
			{
				ballowner->GetGame()->GameOver();
			}
			break;
		}
	}

}