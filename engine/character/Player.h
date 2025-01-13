#pragma once

#include <SDL2/SDL.h>

#include "../GameWorld.h"
#include "../Component.h"
#include "../input/InputComponent.h"
#include "../animation/PlayerAnimationAsset.h"

class GameWorld;

class Player : public Component {

    private:
        SDL_Renderer* renderer;
        PlayerAnimationAsset* anim_asset;
        InputComponent* input_component = nullptr;
        int movement_speed = 0;

    public:

        void update();
        void render(SDL_Renderer* renderer);

        void set_movement_speed(int speed);
        int get_movement_speed();

        void set_anim_asset(PlayerAnimationAsset* asset);
        PlayerAnimationAsset* get_anim_asset();


        template<typename T> void add_component(T* arg);

        void setup_anim_asset(PlayerAnimationAsset* anim_asset);
        void setup_input_component(InputComponent* input_component);

        void handle_input(SDL_Event event);
        
};
