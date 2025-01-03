#pragma once

#include <SDL2/SDL.h>

#include "../GameWorld.h"
#include "../Component.h"
#include "../animation/AnimationAsset.h"

class Player : public Component {

    private:
        SDL_Renderer* renderer;
        AnimationAsset* anim_asset;

    public:

        void update();
        void render(SDL_Renderer* renderer);

        void set_anim_asset(AnimationAsset* asset);
        AnimationAsset* get_anim_asset();


        template<typename T> void add_component(T* arg);

        void setup_anim_asset(AnimationAsset* anim_asset);
        
};
