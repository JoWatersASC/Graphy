#include<SDL2/SDL_image.h>

#include"Application.hpp"

void Application::HandleEvent(SDL_Event* e) {
    g.handleEvent(e);

    if (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED) {
        int drawWidth, drawHeight;
        SDL_GetWindowSize(m_window, &drawWidth, &drawHeight);
        m_ContentWindow.drawTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, drawWidth, drawHeight);
        SDL_SetTextureBlendMode(m_ContentWindow.drawTexture, SDL_BLENDMODE_BLEND);
    }
}

void Application::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    m_window = SDL_CreateWindow("Graph Maker", 200, 60, 1280, 680, SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED & SDL_RENDERER_TARGETTEXTURE);
    bg_name = "../assets/grid.png";
    g = Graph();

    {
        SDL_Surface* tempSurface = IMG_Load(bg_name.c_str());
        m_ContentWindow.bgTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        int bgWidth, bgHeight;
        SDL_QueryTexture(m_ContentWindow.bgTexture, nullptr, nullptr, &bgWidth, &bgHeight);
        m_ContentWindow.bgRect = { 0, 0, bgWidth, bgHeight };

        int drawWidth, drawHeight;
        SDL_GetWindowSize(m_window, &drawWidth, &drawHeight);
        m_ContentWindow.drawTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, drawWidth, drawHeight);
        SDL_SetTextureBlendMode(m_ContentWindow.drawTexture, SDL_BLENDMODE_BLEND);
    }
    

    Node a(vec2(140, 80), "A");
    Node b(vec2(500, 177), "B");
    Node c(vec2(238, 402), "C");

    g.addNode(a);
    g.addNode(b);
    g.addNode(c);
}

void Application::Run() {
    bool running = true;    

    while (running) {
        while (SDL_PollEvent(&e)) {
            Application::HandleEvent(&e);
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
            }
        }

        Render();
    }

    End();
}

void Application::End() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    exit(0);
}

void Application::Render() {
    //Render background
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_ContentWindow.bgTexture, &m_ContentWindow.bgRect, &m_ContentWindow.bgRect);

    //Render drawing area
    SDL_SetRenderTarget(m_renderer, m_ContentWindow.drawTexture);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);
    g.render(m_renderer);

    //Set target back to m_window and draw textures
    SDL_SetRenderTarget(m_renderer, NULL);
    SDL_RenderCopy(m_renderer, m_ContentWindow.drawTexture, NULL, NULL);

    SDL_RenderPresent(m_renderer);
}