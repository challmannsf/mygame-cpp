#include "Player.h"

template void Player::add_component<PlayerAnimationAsset>(PlayerAnimationAsset*);
//template void Player::add_component<AnimationAsset>(AnimationAsset*);
template void Player::add_component<InputComponent>(InputComponent*);

template<typename T> void Player::add_component(T* arg) {
    Component::add_component(*arg); // Calling base class
    
    if constexpr (std::is_base_of<PlayerAnimationAsset, T>::value) {
        this->setup_anim_asset(arg);
    }
    if constexpr (std::is_base_of<InputComponent, T>::value) {
        this->setup_input_component(arg);
    }
    if constexpr (std::is_base_of<CombatSystem, T>::value) {
        this->setup_combat_system(arg);
    }
}

/**
 * All animation related updates needs to be perfomed here
 */
void Player::update() {

    if (this->get_movement_speed() != 0) {
        this->move();
        if (this->anim_asset->get_render_state() != AnimationAsset::render_states::WALKING) {
            this->anim_asset->play_animation_walking();
        }
    } else if (this->get_movement_speed() == 0) {
        if (this->anim_asset->get_render_state() != AnimationAsset::render_states::IDLE) {
            this->anim_asset->play_animation_idle();
        }
    }
    this->anim_asset->update();
}


void Player::set_anim_asset(PlayerAnimationAsset* asset) {
    this->anim_asset = asset;
}

void Player::set_movement_speed(int speed) {
    this->movement_speed = speed;
}

void Player::move() {
    SDL_Rect dest_rect = this->anim_asset->get_dest_rect();
    dest_rect.x += this->movement_speed;
    this->anim_asset->set_dest_rect(dest_rect);
}

int Player::get_movement_speed() { 
    return this->movement_speed;
}

void Player::handle_input(SDL_Event event) {
    if (this->input_component == nullptr) {
        const char* msg = "Input not setup";
        std::cerr <<  SDL_GetError() << std::endl;
        throw GameException(msg, GameException::ABORT);
    }

    this->input_component->set_player(this);
    this->input_component->handle_input(event);
}

void Player::setup_input_component(InputComponent* input_component) {
    this->input_component = input_component;
}

PlayerAnimationAsset* Player::get_anim_asset() {
    return this->anim_asset;
}

void Player::render(SDL_Renderer* renderer) {
    this->anim_asset->render(renderer);
}

void Player::setup_anim_asset(PlayerAnimationAsset* anim_asset) {
    anim_asset->load_textures(this->get_world()->get_renderer());

    // TODO - this is actually related to the sprite 
    // If we now load a different texture we need to update the src_rect and dest_rect
    int sprite_width = 100;
    int sprite_height = 130;
    SDL_Rect src_rect = {0, 0, sprite_width, sprite_height};
    anim_asset->set_src_rect(src_rect);

    SDL_Rect dest_rect = {  0, 
                            SCREEN_HEIGHT / 2 - sprite_height / 2, 
                            sprite_width, 
                            sprite_height
                        };
    anim_asset->set_dest_rect(dest_rect);


    // Set the animation asset which is used for the current player
    this->set_anim_asset(anim_asset);
}

void Player::setup_combat_system(CombatSystem* combat_system) {
    // TODO work on this
    this->combat_system = combat_system;
}


void Player::attack() {
    // TODO - implement
}


