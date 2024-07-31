#pragma once

#include"Graph.hpp"

class Application {
private:
	static Graph g;
public:
	Application() = default;

	static void Run();
	static void End();

	static void HandleEvent(SDL_Event*);
};