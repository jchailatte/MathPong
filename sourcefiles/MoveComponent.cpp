#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	// TODO: Implement in Part 3
	mOwner->SetRotation(mOwner->GetRotation() + mAngularSpeed*deltaTime);
	mOwner->SetPosition (Vector2(mOwner->GetPosition().x + (mOwner->GetForward().x)*mForwardSpeed*deltaTime,
		mOwner->GetPosition().y + (mOwner->GetForward().y) *mForwardSpeed*deltaTime));
}
