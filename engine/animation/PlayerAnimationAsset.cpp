#include "PlayerAnimationAsset.h"


PlayerAnimationAsset::PlayerAnimationAsset() : AnimationAsset() {
    this->set_render_state(AnimationAsset::render_states::IDLE);
} 

void PlayerAnimationAsset::play_animation_walking() {
    // TODO
    this->set_render_state(AnimationAsset::render_states::WALKING);
}

void PlayerAnimationAsset::play_animation_idle() {
    this->set_render_state(AnimationAsset::render_states::IDLE);
}

