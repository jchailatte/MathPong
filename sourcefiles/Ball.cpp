#include "Ball.h"
#include "Random.h"

Ball::Ball (class Game* game)
	:Actor(game)
{
	mSprite = new SpriteComponent(this, 110);
	mComponent = new BallMove(this);
	mCollision = new CollisionComponent(this);

	ballgame = game;
	mSprite->SetTexture(game->GetTexture("Assets/Ball.png"));
	mPosition = Vector2(510, 730);
	mRotation = (Math::Pi)/2;
	mCollision->SetSize(20,20);
}

void Ball::ActorInput(const Uint8* keyState)
{
	if (keyState[SDL_SCANCODE_UP])
	{	
		mComponent->SetForwardSpeed(200);
	}
	else if (keyState[SDL_SCANCODE_DOWN])
	{
		mComponent->SetForwardSpeed(-200);
	}
	else
	{
		mComponent->SetForwardSpeed(0);
	}
}