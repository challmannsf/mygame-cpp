#pragma once

#include "AnimationAsset.h"

class PlayerAnimationAsset : public AnimationAsset {


    public:
        void play_animation_walking();
        void play_animation_idle();
     

        PlayerAnimationAsset();
};