#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	// TODO: Implement
	if (this->GetMax().x < other->GetMin().x)	//to the right
	{
		return false;
	}
	if (this->GetMin().x > other->GetMax().x)	//to the left
	{
		return false;
	}
	if (this->GetMin().y > other->GetMax().y)	//to the bottom			
	{
		return false; 
	}
	if (this->GetMax().y < other->GetMin().y)	//to the top	
	{
		return false;
	}
	return true;
}

Vector2 CollisionComponent::GetMin() const
{
	// TODO: Implement
	Vector2 min;
	min.x = GetCenter().x - (GetWidth() * mOwner->GetScale())/2.0f;
	min.y = GetCenter().y - (GetHeight() * mOwner->GetScale())/2.0f;

	return min;
}

Vector2 CollisionComponent::GetMax() const
{
	// TODO: Implement
	Vector2 max;
	max.x = GetCenter().x + (GetWidth() * mOwner->GetScale())/2.0f;
	max.y = GetCenter().y + (GetHeight() * mOwner->GetScale())/2.0f;

	return max;
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

