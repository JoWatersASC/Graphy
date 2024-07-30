#pragma once

#include"Graph.hpp"

class Application {
private:
	static Graph g;
public:
	Application() = default;

	static void Initialize();
	static void Run();
	static void End();

	static void HandleEvent(SDL_Event*);
};