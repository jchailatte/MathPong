#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

class Block : public Actor
{
public:
	Block(class Game* game, std::string file);
	~Block();

	std::string value;
	class Game* blockgame;
};