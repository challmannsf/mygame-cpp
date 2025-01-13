#include "GameWorld.h"


GameWorld::GameWorld() {    

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << SDL_GetError() << std::endl;
        const char* msg = "Failed to initialize SDL";
        throw GameException(msg, GameException::ABORT);
    }

    this->window = SDL_CreateWindow(
        "Sprite Animation Example",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!this->window) {
        const char* msg = "Failed to create window";
        std::cerr <<  SDL_GetError() << std::endl;
        throw GameException(msg, GameException::ABORT);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->renderer) {
        std::cerr << SDL_GetError() << std::endl;
        const char* msg = "Failed to create renderer";
        throw GameException(msg, GameException::ABORT);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << IMG_GetError() << std::endl;
        const char* msg = "Failed to initialize PNG support! SDL_image Error";
        throw GameException(msg, GameException::ABORT);
    }

    this->img_initiated = true;

}

/**
 * Ensure cleanup of all SDL data
 */
GameWorld::~GameWorld() {
    std::cout << "Gameworld shutdown" << std::endl;

    if (this->renderer != nullptr) {
        SDL_DestroyRenderer(this->renderer);
    }
    if (this->window != nullptr) {
        SDL_DestroyWindow(window);
    }
    if (this->img_initiated == true) {
        IMG_Quit();
    }
    SDL_Quit();  

    for (auto component : components) {
        delete component;
    }
}

SDL_Window* GameWorld::get_window() {
    return this->window;
}


SDL_Renderer* GameWorld::get_renderer() {
    return this->renderer;
} 


void GameWorld::update() {
    for (auto &component : this->components) {
        component->update();
    }
}


void GameWorld::render() {
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(this->renderer);

    for (auto &component : this->components) {
        component->render(this->renderer);
    }

    // render anything here from the gameworld
    // SDL_RenderCopy(this->renderer, spriteSheet, &srcRect, &destRect);

    // Update the screen
    SDL_RenderPresent(this->renderer);

    // Delay to control frame rate
    SDL_Delay(16); // ~60 FPS

   
}
void GameWorld::add_component(Component* component) {
    this->components.push_back(component);
}

/**
 * TODO - separat into an input component later on
 */
void GameWorld::handle_input(SDL_Event event) {
    // The player is known to the world
    // sent the input to the player
    for (auto &component : this->components) {
        // Loop through all components until the player is found and handle the input ?
        if (Player* player = dynamic_cast<Player*>(component)) {
            player->handle_input(event);
        }
    }

   
}