#include "InputComponent.h"

InputComponent::InputComponent() {}
InputComponent::~InputComponent() {}

void InputComponent::set_player(Player* player) {
    this->player = player;
}

void InputComponent::handle_input(SDL_Event event) {
    if(event.type == SDL_KEYDOWN) {
        // Increase speed
        if (event.key.keysym.sym == SDLK_RIGHT) {
            this->player->set_movement_speed(1);
        }
        if (event.key.keysym.sym == SDLK_f) {
            this->player->attack(); // TODO - pass what kind of attak
        }
    }
    if (event.type == SDL_KEYUP) {
       if (event.key.keysym.sym == SDLK_RIGHT) {
            this->player->set_movement_speed(0);
        }
    }
}
