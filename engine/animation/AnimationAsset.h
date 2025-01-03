#pragma once

#include <iostream>

#include "../Component.h"

class AnimationAsset : public Component {

    private:
        std::string texture_path;
        SDL_Texture* anim_texture;
        int current_frame = 0;
        Uint32 last_frame_time;
        int num_frames;

        int sprite_width = 100;  // Width of each frame in the sprite sheet
        int sprite_height = 130; // Height of each frame in the sprite sheet

        // Source rectangle (portion of the sprite sheet to render)
        SDL_Rect src_rect;

        // Destination rectangle (position and size on the screen)
        SDL_Rect dest_rect;

    public:

        AnimationAsset();
        ~AnimationAsset();
        void load_texture(SDL_Renderer* renderer);

        void set_texture_path(std::string path);
        const std::string get_texture_path();

        void set_anim_texture(SDL_Texture* texture);
        SDL_Texture* get_anim_texture();

        void update() override;
        void render(SDL_Renderer* renderer) override;

        void set_num_frames(int num_frames);
        void set_src_rect(SDL_Rect src_rect);
        SDL_Rect get_src_rect();

        void set_dest_rect(SDL_Rect dest_rect);
        SDL_Rect get_dest_rect();
};