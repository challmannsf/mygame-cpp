
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "engine/GameWorld.h"
#include "engine/character/Player.h"
#include "engine/animation/PlayerAnimationAsset.h"
#include "engine/input/InputComponent.h"
#include "engine/combat/CombatSystem.h"


int main(int argc, char* argv[]) {

    GameWorld* world;
    Player* main_player;
    PlayerAnimationAsset* anim_asset; 
    InputComponent* input_component;
    CombatSystem* combat_system;


    try {
        world = new GameWorld();
        // TODO - move to a setup player method
        main_player = new Player();
        anim_asset = new PlayerAnimationAsset();
        anim_asset->add_texture_path(AnimationAsset::render_states::IDLE, "asset/chars/hero/Idle.png", 5);
        anim_asset->add_texture_path(AnimationAsset::render_states::WALKING, "asset/chars/hero/Walk.png", 7);
        anim_asset->add_texture_path(AnimationAsset::render_states::ATTACKING, "asset/chars/hero/Attack_3.png", 7);
        main_player->set_world(world);
        main_player->add_component<PlayerAnimationAsset>(anim_asset);

        input_component = new InputComponent();
        main_player->add_component<InputComponent>(input_component);

        combat_system = new CombatSystem();
       // combat_system->add_skill(CombatSkill::ATTACK);
        main_player->add_component<CombatSystem>(combat_system);

        main_player->get_anim_asset()->load_textures(world->get_renderer());
        // place a player in the world
        world->add_component(main_player);
    } catch (const GameException& exc) { // Catch by const reference
        if (exc.get_exception_category() == GameException::ABORT) {
            delete main_player;
            delete world;
            delete anim_asset;
            delete input_component;
            delete combat_system;
            return -1;
        }
    }


    // Main game loop
    bool running = true;
    SDL_Event event;

    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }

            world->handle_input(event);
        }

        // Update the game world with all components
        // this includes also animations
        world->update();

        // Clear the screen
        world->render();
     
    }

    // Cleanup
    delete world;

    return 0;
}

