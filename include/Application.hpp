#pragma once

#include"Graph.hpp"

class Application {
public:
	Application() = default;

	static void Init();
	static void Run();
	static void End();

	static void HandleEvent(SDL_Event*);

private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_Event e;

	static std::string bg_name;
	static Graph g;
};