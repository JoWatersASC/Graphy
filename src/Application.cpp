#include"Application.hpp"

Graph Application::g;

void Application::HandleEvent(SDL_Event* e) {
    g.handleEvent(e);
}

void Application::Run() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(1280, 680, 0, &window, &renderer);

    bool running = true;
    int count = 0;

    Node a(vec2(140, 80), "A");
    Node b(vec2(500, 177), "B");
    Node c(vec2(238, 402), "C");

    g.addNode(a);
    g.addNode(b);
    g.addNode(c);

    while (running) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e)) {
            Application::HandleEvent(&e);
            if (e.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }
        }

        /*for(auto node : nodes)
        node.render(renderer);*/

        g.render(renderer);

        SDL_RenderPresent(renderer);
    }
}