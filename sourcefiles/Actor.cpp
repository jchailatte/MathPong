#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "MoveComponent.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	, mState(EActive)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
{
	// TODO
	mGame->AddActor(this);
	mSprite = nullptr;
	mComponent = nullptr;
	mCollision = nullptr;
}

Actor::~Actor()
{
	// TODO
	mGame->RemoveActor(this);
	delete mSprite;
	delete mComponent;
	delete mCollision;
}

void Actor::Update(float deltaTime)
{
	// TODO
	if(mState == EActive)
	{
		if (mComponent != nullptr)
		{
			mComponent->Update(deltaTime);
		}
		if (mSprite != nullptr)
		{
			mSprite->Update(deltaTime);
		}
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	// TODO
	if (mState == EActive)
	{
		if (mComponent != nullptr)
		{
			mComponent->ProcessInput(keyState);
		}
		if (mSprite != nullptr)
		{
					mSprite->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const Uint8* keyState)
{
}

SpriteComponent* Actor::GetSprite()
{
	return mSprite;
}

void Actor::SetSprite(SpriteComponent* temp)
{
	mSprite = temp;
}

Vector2 Actor::GetForward()
{
	float x = cos(mRotation);
	float y = -1*sin(mRotation);
	return Vector2(x, y);
}

MoveComponent* Actor::GetComponent()
{
	return mComponent;
}

CollisionComponent* Actor::GetCollision()
{
	return mCollision;
}