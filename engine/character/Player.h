#pragma once

#include <SDL2/SDL.h>

#include "../GameWorld.h"
#include "../Component.h"
#include "../input/InputComponent.h"
#include "../animation/PlayerAnimationAsset.h"
#include "../combat/CombatSystem.h"

class GameWorld;
class InputComponent;

class Player : public Component {

    private:
        SDL_Renderer* renderer;
        PlayerAnimationAsset* anim_asset;
        InputComponent* input_component = nullptr;
        CombatSystem* combat_system = nullptr;
        int movement_speed = 0;

    public:


        void update();
        void render(SDL_Renderer* renderer);

        void set_movement_speed(int speed);
        int get_movement_speed();


        void attack();

        void set_anim_asset(PlayerAnimationAsset* asset);
        PlayerAnimationAsset* get_anim_asset();


        template<typename T> void add_component(T* arg);

        void setup_anim_asset(PlayerAnimationAsset* anim_asset);
        void setup_input_component(InputComponent* input_component);
        void setup_combat_system(CombatSystem* combat_system);

        void handle_input(SDL_Event event);

        void move();
        
};
