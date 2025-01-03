#include "Player.h"

template void Player::add_component<AnimationAsset>(AnimationAsset*);

template<typename T> void Player::add_component(T* arg) {
    Component::add_component(*arg); // Calling base class
    
    if (std::is_base_of<AnimationAsset, T>::value) {
        this->setup_anim_asset(arg);
    }
}

void Player::update() {
    this->anim_asset->update();
}


void Player::set_anim_asset(AnimationAsset* asset) {
    this->anim_asset = asset;
}


AnimationAsset* Player::get_anim_asset() {
    return this->anim_asset;
}

void Player::render(SDL_Renderer* renderer) {
    this->anim_asset->render(renderer);
}

void Player::setup_anim_asset(AnimationAsset* anim_asset) {
    anim_asset->load_texture(this->get_world()->get_renderer());
    int sprite_width = 100;
    int sprite_height = 130;
    SDL_Rect src_rect = {0, 0, sprite_width, sprite_height};
    anim_asset->set_src_rect(src_rect);

    SDL_Rect dest_rect = {  SCREEN_WIDTH / 2 - sprite_width / 2, 
                            SCREEN_HEIGHT / 2 - sprite_height / 2, 
                            sprite_width, 
                            sprite_height
                            };
    anim_asset->set_dest_rect(dest_rect);


    this->set_anim_asset(anim_asset);
}

