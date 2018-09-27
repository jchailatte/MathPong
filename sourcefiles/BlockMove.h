#include "MoveComponent.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Math.h"
#include "Block.h"
#include "Game.h"
#include "Random.h"

class BlockMove : public MoveComponent
{
public:
	BlockMove(class Actor* owner);

	void Update(float deltaTime) override;

	Actor* blockowner;
	float rotation = Random::GetFloatRange(0.0f, Math::TwoPi);
	Vector2 velocity = (Vector2(cos(rotation) * 100, sin(rotation) * 100));
};