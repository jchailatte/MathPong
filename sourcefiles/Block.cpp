#include "Block.h"
#include "BlockMove.h"
#include "Game.h"

Block::Block(class Game* game, std::string file)
	:Actor(game)
{
	mSprite = new SpriteComponent(this, 80);
	mCollision = new CollisionComponent(this);
	mComponent = new BlockMove(this);
	blockgame = game;

	mSprite->SetTexture(game->GetTexture(file));
	mCollision->SetSize(48, 48);

	game->AddBlock(this);
}

Block::~Block()
{
	blockgame->RemoveBlock(this);
}

