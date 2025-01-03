#include "Component.h"


Component::Component() {}

Component::~Component() {

}

GameWorld* Component::get_world() {
    return this->world;
}

void Component::set_world(GameWorld* world) {
    this->world = world;
}

void Component::update() {
    // Placeholder
}

void Component::render(SDL_Renderer* renderer) {
    // Placeholder
}

