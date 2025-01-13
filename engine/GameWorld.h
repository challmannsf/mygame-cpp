#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Component.h"
#include "character/Player.h"
#include "utils/GameException.h"


class GameWorld {


    private:

        std::vector<Component*> components; // List of all objects in the game

        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;
        const int SPRITE_WIDTH = 100;  // Width of each frame in the sprite sheet
        const int SPRITE_HEIGHT = 130; // Height of each frame in the sprite sheet
        const int NUM_FRAMES = 6;     // Total number of frames in the animation
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool img_initiated = false;

    public: 

        const int FRAME_TIME = 100;   // Time per frame in milliseconds
        GameWorld();
        ~GameWorld();

        SDL_Window* get_window();
        SDL_Renderer* get_renderer();

        void handle_input(SDL_Event event);
        void update();
        void render();
        void add_component(Component* component);



};