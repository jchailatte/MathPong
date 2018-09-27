#include "Game.h"
#include "Actor.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Random.h"
#include <vector>
#include <string>
#include <cstring>
#include "Ball.h"

Game::Game()
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
		"Math Pong",						// window title
		SDL_WINDOWPOS_UNDEFINED,            // initial x position
		SDL_WINDOWPOS_UNDEFINED,            // initial y position
		1024,                               // width, in pixels
		770,                                // height, in pixels
		SDL_WINDOW_OPENGL                   // flags - see below
	);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	std::ifstream level("Assets/Problems.txt");
	std::string line;
	if (level.is_open())
	{
		while (getline(level, line))
		{
			problems.push_back(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			solutions.push_back(line);
		}
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	LoadData();
	return 1;
}

void Game::RunLoop()
{
	while (flag == true)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {							//exit using the 'x' or esc

		if (event.type == SDL_QUIT)
		{
			flag = false;
		}	
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		flag = false;
	}

	std::vector<Actor*> temp = actors;
	for (int i = 0; i < temp.size(); i++)
	{
		temp[i]->ProcessInput(state);
	}
	
}

void Game::GenerateOutput()
{  									//r g   b   a
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	
	for (int i = 0; i < mSprites.size(); i++)
	{
		mSprites[i]->Draw(renderer);
	}

	TTF_Font* Sans = TTF_OpenFont("Assets/open-sans/OpenSans-Bold.ttf", 24); 
	SDL_Color White = { 255, 255, 255 };  
	surfaceMessage = TTF_RenderText_Solid(Sans, displaytxt.c_str(), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; 
	Message_rect.x = 450;   
	Message_rect.y = 100;
	Message_rect.w = 100;
	Message_rect.h = 50; 
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); 
	TTF_CloseFont(Sans);

	SDL_RenderPresent(renderer);
}

void Game::UpdateGame()
{										

	while (SDL_GetTicks() < last_tick_time + 16)			//restricting fps to ~60
	{
	}

	float tick_time = SDL_GetTicks();
	delta = (tick_time - last_tick_time) / 1000.0;
	if (delta > 0.05)										//frame time cap
	{
		delta = 0.05;
	}
	last_tick_time = tick_time;

	std::vector<Actor*> temp = actors;
	for (int i = 0; i < temp.size(); i++)
	{
		temp[i]->Update(delta);
	}

	std::vector<Actor*> dead;
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i]->GetState() == Actor::EDead)
		{
			dead.push_back(temp[i]);
		}
	}

	for (int i = 0; i < dead.size(); i++)
	{
		delete dead[i];
	}

}

void Game::AddActor(Actor* temp)
{
	actors.push_back(temp);
}

void Game::RemoveActor(Actor* temp)
{
	actors.erase(std::find(actors.begin(), actors.end(), temp));
}

SDL_Texture* Game::GetTexture(std::string file)
{
	if (textures.find(file) == textures.end())
	{
		SDL_Surface *tempimage = IMG_Load(file.c_str());
		SDL_Texture *temptext = SDL_CreateTextureFromSurface(renderer, tempimage);
		SDL_FreeSurface(tempimage);
		tempimage = NULL;

		textures[file] = temptext;
		return temptext;
	}
	else
	{
		return textures[file];
	}
}

void Game::AddSprite(SpriteComponent* mSprite)
{
	mSprites.push_back(mSprite);
	std::sort(mSprites.begin(), mSprites.end(),
		[](SpriteComponent* a, SpriteComponent* b) {
		return a->GetDrawOrder() < b->GetDrawOrder();
	});
}

void Game::RemoveSprite(SpriteComponent* mSprite)
{
	mSprites.erase(std::find(mSprites.begin(), mSprites.end(), mSprite));
}

void Game::AddBlock(Block* mBlock)
{
	mBlocks.push_back(mBlock);
}

void Game::RemoveBlock(Block* mBlock)
{
	mBlocks.erase(std::find(mBlocks.begin(), mBlocks.end(), mBlock));
}

std::vector<Block*> Game::GetBlocks()
{
	return mBlocks;
}

void Game::SetSolution(std::string sol)
{
	solution = sol;
}

std::string Game::GetSolution()
{
	return solution;
}

void Game::LoadData()
{
	Actor* background = new Actor(this);
	background->SetPosition(Vector2(512, 384));
	SpriteComponent* backgroundsc = new SpriteComponent(background, 50);
	backgroundsc->SetTexture(GetTexture("Assets/Background.png"));
	background->SetSprite(backgroundsc);

	Actor* background2 = new Actor(this);
	background2->SetPosition(Vector2(512, 384));
	SpriteComponent* background2sc = new SpriteComponent(background2, 50);
	background2sc->SetTexture(GetTexture("Assets/background2.png"));
	background2->SetSprite(background2sc);

	Block* block = new Block(this, "Assets/num" + solutions[0] + ".png");
	block->SetPosition(Vector2(100, 100));
	block->value = solutions[0];

	std::string a = std::to_string(Random::GetIntRange(1, 9));
	Block* block2 = new Block(this, "Assets/num" + a + ".png");
	block2->SetPosition(Vector2(100, 400));
	block2->value = a;
	
	a = std::to_string(Random::GetIntRange(1, 9));
	Block* block3 = new Block(this, "Assets/num" + a + ".png");
	block3->SetPosition(Vector2(100, 700));
	block3->value = a;

	a = std::to_string(Random::GetIntRange(1, 9));
	Block* block4 = new Block(this, "Assets/num" + a + ".png");
	block4->SetPosition(Vector2(670, 100));
	block4->value = a;

	a = std::to_string(Random::GetIntRange(1, 9));
	Block* block5 = new Block(this, "Assets/num" + a + ".png");
	block5->SetPosition(Vector2(670, 400));
	block5->value = a;

	a = std::to_string(Random::GetIntRange(1, 9));
	Block* block6 = new Block(this, "Assets/num" + a + ".png");
	block6->SetPosition(Vector2(670, 700));
	block6->value = a;

	displaytxt = problems[0];

	SetSolution(solutions[0]);
	solutions.erase(solutions.begin());
	problems.erase(problems.begin());

	Ball* ball = new Ball(this);
}

void Game::ReLoadNumbers(int blockhit)
{
	if (problems.empty())
	{
		for (int i = 0; i < mBlocks.size(); i++)
		{
			mBlocks[i]->SetState(Actor::EDead);
		}
		SDL_DestroyTexture(textures["Assets/Ball.png"]);
		displaytxt = "";

		Actor* win= new Actor(this);
		win->SetPosition(Vector2(512, 384));
		SpriteComponent* winsc = new SpriteComponent(win, 50);
		winsc->SetTexture(GetTexture("Assets/win.png"));
		win->SetSprite(winsc);
		return;
	}
	
	int rand = Random::GetIntRange(0, 5);
	while (rand == blockhit)
	{
		rand = Random::GetIntRange(0, 5);
	}

	for (int i = 0; i < mBlocks.size();i++)
	{
		if (i == rand)
		{
			mBlocks[i]->GetSprite()->SetTexture(this->GetTexture("Assets/num" + solutions[0] + ".png"));
			mBlocks[i]->value = solutions[0];
		}
		else
		{
			std::string a = std::to_string(Random::GetIntRange(1, 9));
			mBlocks[i]->GetSprite()->SetTexture(this->GetTexture("Assets/num" + a +".png"));
			mBlocks[i]->value = a;
		}
	}
	displaytxt = problems[0];
	SetSolution(solutions[0]);

	solutions.erase(solutions.begin());
	problems.erase(problems.begin());
}

void Game::GameOver()
{
	for (int i = 0; i < mBlocks.size(); i++)
	{
		mBlocks[i]->SetState(Actor::EDead);
	}
	SDL_DestroyTexture(textures["Assets/Ball.png"]);
	displaytxt = "";

	Actor* win = new Actor(this);
	win->SetPosition(Vector2(512, 384));
	SpriteComponent* winsc = new SpriteComponent(win, 50);
	winsc->SetTexture(GetTexture("Assets/GameOver.png"));
	win->SetSprite(winsc);
}

void Game::UnloadData()
{
	for (std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}

	textures.clear();
}

void Game::Shutdown()
{
	SDL_FreeSurface(surfaceMessage);
	UnloadData();
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}