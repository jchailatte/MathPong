#include "MoveComponent.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Math.h"
#include "Block.h"
#include "Game.h"
#include "Random.h"

class BallMove : public MoveComponent
{
public:
	BallMove(class Actor* owner);

	void Update(float deltaTime) override;

	Actor* ballowner;
	Vector2 velocity = Vector2(150, -150);
	bool collision;
};