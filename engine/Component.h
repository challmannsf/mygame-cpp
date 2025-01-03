#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils/GameException.h"
#include "utils/GameConstants.h"

// Forward declaration of GameWorld class
class GameWorld;

/**
 * Base class to all objects within the game
 */
class Component {

    int width;
    int height;

    private:
        GameWorld* world;



    public:
        Component();
        ~Component();


        // A component must be part of the world to be active.
        // dont forget to set the world
        void set_world(GameWorld* world);
        GameWorld* get_world();

        virtual void update();
        virtual void render(SDL_Renderer* renderer);

        template<typename T> void add_component(T arg) {
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        }
    
        
};