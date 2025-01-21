#pragma once

#include <iostream>

#include "../Component.h"

class AnimationAsset : public Component {
    
    public:
        struct render_states {
            static const std::string IDLE;
            static const std::string WALKING;
            static const std::string ATTACKING;
        };

        struct texture_data {
            std::string path;
            int number_of_frames;
            SDL_Texture* texture;
        };

    private:
      
        // TODO both seems a bit redundant.  check later on
        std::map<std::string, texture_data> texture_paths;
        std::map<std::string, texture_data> anim_textures;
        int current_frame = 0;
        Uint32 last_frame_time;
        int num_frames;
        int sprite_width = 100;  // Width of each frame in the sprite sheet
        int sprite_height = 130; // Height of each frame in the sprite sheet

        // Source rectangle (portion of the sprite sheet to render)
        SDL_Rect src_rect;

        // Destination rectangle (position and size on the screen)
        SDL_Rect dest_rect;

        SDL_Rect previous_dest_rect;

        // The current state of the animation to render the texture for
        std::string current_render_state; 

    public:

        AnimationAsset();
        ~AnimationAsset();
        void load_textures(SDL_Renderer* renderer);

        void add_texture_path(std::string name, std::string path, int number_of_frames);
        const std::map<std::string, texture_data> get_texture_paths();

        void add_anim_texture(std::string anim_name, SDL_Texture* texture, int number_of_frames);
        
        std::map<std::string, texture_data> get_anim_textures();

        void update() override;
        void render(SDL_Renderer* renderer) override;

        // @deprecated
        void set_num_frames(int num_frames);
        void set_src_rect(SDL_Rect src_rect);
        SDL_Rect get_src_rect();

        void set_dest_rect(SDL_Rect dest_rect);
        SDL_Rect get_dest_rect();

        void set_previous_dest_rect(SDL_Rect dest_rect);
        SDL_Rect get_previous_dest_rect();

        void set_render_state(const std::string& state);
        const std::string& get_render_state();
};