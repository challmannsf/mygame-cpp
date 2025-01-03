
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "engine/animation/AnimationAsset.h"
#include "engine/GameWorld.h"
#include "engine/character/Player.h"


int main(int argc, char* argv[]) {

    GameWorld* world;
    Player* main_player;
    AnimationAsset* anim_asset; 
    SDL_Texture* spriteSheet;


    try {
        world = new GameWorld();
        main_player = new Player();
        anim_asset = new AnimationAsset(); // set lastFRametime
        anim_asset->set_num_frames(6);
        anim_asset->set_texture_path("asset/chars/hero/Idle.png");
        main_player->set_world(world);
        main_player->add_component<AnimationAsset>(anim_asset);
        main_player->get_anim_asset()->load_texture(world->get_renderer());
        spriteSheet = main_player->get_anim_asset()->get_anim_texture();

        // place a player in the world
        world->add_component(main_player);
    } catch (const GameException& exc) { // Catch by const reference
        if (exc.get_exception_category() == GameException::ABORT) {
            delete main_player;
            delete world;
            delete anim_asset;
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
                world->handle_input(event);
            }
        }

        // Update the game world with all components
        // this includes also animtions
        world->update();

        // Clear the screen
        world->render(spriteSheet, main_player->get_anim_asset()->get_src_rect(), main_player->get_anim_asset()->get_dest_rect());
    
      
    }

    // Cleanup
    delete world;

    return 0;
}

