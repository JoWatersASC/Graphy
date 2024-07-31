#pragma once

#include"Graph.hpp"

class Application {
public:
	Application() = default;

	void Init();
	void Run();
	void End();

	void HandleEvent(SDL_Event*);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event e;
	std::string bg_name;
	Graph g;

	void Render(SDL_Texture* bgTexture, SDL_Rect& bgRect, SDL_Texture* drawTexture);
};