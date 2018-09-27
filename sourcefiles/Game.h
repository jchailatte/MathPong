#pragma once

#include "SDL/SDL.h"
#include "Actor.h"
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include "SpriteComponent.h"
#include <fstream>
#include "Block.h"

class Game {
public:
	Game();

	bool Initialize();
	void Shutdown();
	void RunLoop();
		void ProcessInput();
		void UpdateGame();
		void GenerateOutput();
	void AddActor(Actor*);
	void RemoveActor(Actor*); 
	SDL_Texture* GetTexture(std::string);
	void AddSprite(SpriteComponent*);
	void RemoveSprite(SpriteComponent*);
	void AddBlock(Block*);
	void RemoveBlock(Block*);
	std::vector<Block*> GetBlocks();
	void ReLoadNumbers(int);
	void GameOver();
	
	std::string GetSolution();
	void SetSolution(std::string);

private: 
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface* surfaceMessage;
	bool flag = true;
	float last_tick_time = 0;
	float delta = 0;
	SDL_Texture *background;
	std::string solution;
	std::string displaytxt;

	std::map<std::string, SDL_Texture*> textures;
	std::vector<Actor*> actors;
	std::vector<SpriteComponent*> mSprites;
	std::vector<Block*> mBlocks;
	std::vector<std::string> problems;
	std::vector<std::string> solutions;

	void LoadData();
	void UnloadData();
};


