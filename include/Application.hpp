#pragma once

#include"Graph.hpp"

struct ContentWindow {
	SDL_Texture* bgTexture;
	SDL_Rect bgRect;
	SDL_Texture* drawTexture;
};

class Application {
public:
	Application() = default;

	void Init();
	void Run();
	void End();

	void HandleEvent(SDL_Event*);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event e;
	std::string bg_name;
	Graph g;

	ContentWindow m_ContentWindow;

	void Render();
};