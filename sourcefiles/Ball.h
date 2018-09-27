#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "BallMove.h"

class Ball: public Actor
{
public:
	Ball(class Game* game);
	class Game* ballgame;
	void ActorInput(const Uint8* keyState) override;
};
