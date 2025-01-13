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

    private:
        std::string texture_path;
        std::map<std::string, std::string> texture_paths;
        SDL_Texture* anim_texture;
        std::map<std::string, SDL_Texture*> anim_textures;
        int current_frame = 0;
        Uint32 last_frame_time;
        int num_frames;
        int sprite_width = 100;  // Width of each frame in the sprite sheet
        int sprite_height = 130; // Height of each frame in the sprite sheet

        // Source rectangle (portion of the sprite sheet to render)
        SDL_Rect src_rect;

        // Destination rectangle (position and size on the screen)
        SDL_Rect dest_rect;

        // The current state of the animation to render the texture for
        std::string current_render_state; 

    public:

        AnimationAsset();
        ~AnimationAsset();
        void load_textures(SDL_Renderer* renderer);

        void add_texture_path(std::string name, std::string path);
        const std::string get_texture_path();

        void add_anim_texture(std::string anim_name, SDL_Texture* texture);
        
        std::map<std::string, SDL_Texture*> get_anim_textures();

        void update() override;
        void render(SDL_Renderer* renderer) override;

        void set_num_frames(int num_frames);
        void set_src_rect(SDL_Rect src_rect);
        SDL_Rect get_src_rect();

        void set_dest_rect(SDL_Rect dest_rect);
        SDL_Rect get_dest_rect();

        void set_render_state(const std::string& state);
        const std::string& get_render_state();
};