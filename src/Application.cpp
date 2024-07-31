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

    Node a(vec2(140, 80), "A");
    Node b(vec2(500, 177), "B");
    Node c(vec2(238, 402), "C");

    g.addNode(a);
    g.addNode(b);
    g.addNode(c);
}

void Application::Run() {
    bool running = true;

    //Background Texture
    SDL_Texture* bgTexture;
    SDL_Rect bgRect;
    //Graph Drawing Texture
    SDL_Texture* drawTexture;

    {
        int bgWidth, bgHeight;
        SDL_Surface* tempSurface = IMG_Load(bg_name.c_str());
        bgTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_QueryTexture(bgTexture, nullptr, nullptr, &bgWidth, &bgHeight);
        bgRect = { 0, 0, bgWidth, bgHeight };
        SDL_FreeSurface(tempSurface);

        int drawWidth, drawHeight;
        SDL_GetWindowSize(window, &drawWidth, &drawHeight);
        drawTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, drawWidth, drawHeight);
        SDL_SetTextureBlendMode(drawTexture, SDL_BLENDMODE_BLEND);
    }

    while (running) {
        while (SDL_PollEvent(&e)) {
            Application::HandleEvent(&e);
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
            }
        }

        Render(bgTexture, bgRect, drawTexture);
    }
}

void Application::End() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    exit(0);
}

void Application::Render(SDL_Texture* bgTexture, SDL_Rect& bgRect, SDL_Texture* drawTexture) {
    //Render background
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTexture, &bgRect, &bgRect);

    //Render drawing area
    SDL_SetRenderTarget(renderer, drawTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    g.render(renderer);

    //Set target back to window and draw textures
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, drawTexture, NULL, NULL);

    SDL_RenderPresent(renderer);
}