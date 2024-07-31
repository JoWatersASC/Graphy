#include<SDL2/SDL_image.h>

#include"Application.hpp"

SDL_Window*   Application::window   = nullptr;
SDL_Renderer* Application::renderer = nullptr;
SDL_Event     Application::e;

std::string Application::bg_name;
Graph       Application::g;

void Application::HandleEvent(SDL_Event* e) {
    g.handleEvent(e);
}

void Application::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Graph Maker", 200, 60, 1280, 680, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bg_name = "../assets/grid.png";
}

void Application::Run() {
    bool running = true;

    Node a(vec2(140, 80), "A");
    Node b(vec2(500, 177), "B");
    Node c(vec2(238, 402), "C");

    g.addNode(a);
    g.addNode(b);
    g.addNode(c);

    SDL_Surface* tempSurface = IMG_Load(bg_name.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    int bgWidth, bgHeight;

    SDL_QueryTexture(tex, nullptr, nullptr, &bgWidth, &bgHeight);
    SDL_Rect bgRect = { 0, 0, bgWidth, bgHeight };

    while (running) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e)) {
            Application::HandleEvent(&e);
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
            }
        }

        SDL_RenderCopy(renderer, tex, &bgRect, &bgRect);
        g.render(renderer);

        SDL_RenderPresent(renderer);
    }
}

void Application::End() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    exit(0);
}