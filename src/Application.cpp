#include<SDL2/SDL_image.h>

#include"Application.hpp"

void Application::HandleEvent(SDL_Event* e) {
    g.handleEvent(e);
}

void Application::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Graph Maker", 200, 60, 1280, 680, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED & SDL_RENDERER_TARGETTEXTURE);
    
    bg_name = "../assets/grid.png";
    g = Graph();
}

void Application::Run() {
    bool running = true;

    Node a(vec2(140, 80), "A");
    Node b(vec2(500, 177), "B");
    Node c(vec2(238, 402), "C");

    g.addNode(a);
    g.addNode(b);
    g.addNode(c);

    SDL_Texture* tex;
    SDL_Texture* drawTx;

    {
        SDL_Surface* tempSurface = IMG_Load(bg_name.c_str());
        tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        int drawWidth, drawHeight;
        SDL_GetWindowSize(window, &drawWidth, &drawHeight);
        drawTx = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, drawWidth, drawHeight);
    }

    int bgWidth, bgHeight;
    SDL_QueryTexture(tex, nullptr, nullptr, &bgWidth, &bgHeight);
    SDL_Rect bgRect = { 0, 0, bgWidth, bgHeight };
    SDL_Rect drRect = { 0, 0, 1280, 680 };

    while (running) {
        while (SDL_PollEvent(&e)) {
            Application::HandleEvent(&e);
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
            }
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetTextureBlendMode(drawTx, SDL_BLENDMODE_BLEND);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, tex, &bgRect, &bgRect);

        SDL_SetRenderTarget(renderer, drawTx);
        SDL_SetRenderDrawColor(renderer, 25, 55, 255, 0);
        //SDL_RenderClear(renderer);
        g.render(renderer);

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, drawTx, NULL, NULL);

        SDL_RenderPresent(renderer);
    }
}

void Application::End() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    exit(0);
}