#include<cmath>

#include"SDL2/SDL.h"
#include"SDL2/SDL2_gfxPrimitives.h"

#include"Application.hpp"

int main(int argc, char* argv[]){
	Application app;
	app.Init();
	app.Run();

	return 0;
}