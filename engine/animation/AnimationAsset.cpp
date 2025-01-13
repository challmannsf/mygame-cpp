#include "AnimationAsset.h"

// Initialize static render state strings
const std::string AnimationAsset::render_states::IDLE = "idle";
const std::string AnimationAsset::render_states::WALKING = "walking";
const std::string AnimationAsset::render_states::ATTACKING = "attacking";

AnimationAsset::AnimationAsset() {
    this->last_frame_time = SDL_GetTicks();
    this->set_render_state(AnimationAsset::render_states::IDLE);
}

AnimationAsset::~AnimationAsset() {
    
}


std::map<std::string, SDL_Texture*> AnimationAsset::get_anim_textures() {
    return this->anim_textures;
}

void AnimationAsset::add_anim_texture(std::string anim_name, SDL_Texture* texture) {
    this->anim_textures[anim_name] = texture;
}


void AnimationAsset::set_num_frames(int num_frames) {
    this->num_frames = num_frames;
}

void AnimationAsset::add_texture_path(std::string name, std::string path) {
    this->texture_path = path;
    this->texture_paths[name] = path;

}

const std::string AnimationAsset::get_texture_path() {
    return this->texture_path;
}

void AnimationAsset::set_src_rect(SDL_Rect src_rect) {
    this->src_rect = src_rect;
}

SDL_Rect AnimationAsset::get_src_rect() {
    return this->src_rect;
}

void AnimationAsset::set_dest_rect(SDL_Rect dest_rect) {
    this->dest_rect = dest_rect;
}

SDL_Rect AnimationAsset::get_dest_rect() {
    return this->dest_rect;
}

void AnimationAsset::set_render_state(const std::string& state) {
    this->current_render_state = state;
}

const std::string& AnimationAsset::get_render_state() {
    return this->current_render_state;
}


void AnimationAsset::load_textures(SDL_Renderer* renderer) {
    for (auto texture_path : this->texture_paths) {
        SDL_Surface* loaded_surface = IMG_Load(texture_path.second.c_str());
        SDL_Texture* new_texture = nullptr;
        if (!loaded_surface) {
            const char* msg =  "Unable to load image";
            std::cerr << texture_path.second << "! SDL_image Error: " << IMG_GetError() << std::endl;
            throw GameException(msg, GameException::ABORT);
        }

        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        SDL_FreeSurface(loaded_surface);
        if (!new_texture) {
            const char* msg = "Unable to load new texture";
            throw GameException(msg, GameException::ABORT);
        }

        this->add_anim_texture(texture_path.first, new_texture);
    }
}

/**
 * TODO understand the frame time handling. 
 * if we set the last frame time from multiple update calls, this can cause the animation to be faster than expected.
 */
void AnimationAsset::update() {
    Uint32 current_time = SDL_GetTicks();
    if (current_time - this->last_frame_time > FRAME_TIME) {
        current_frame = (current_frame + 1) % this->num_frames; // Cycle through frames
        this->src_rect.x = current_frame * (this->src_rect.w + 28);        // @TODO move to a var 28 is the offset of the sprite!
        this->last_frame_time = current_time;
    }
}


void AnimationAsset::render(SDL_Renderer* renderer) {
     std::map<std::string, SDL_Texture*> textures = this->get_anim_textures();
     if (textures.find(this->current_render_state) == textures.end()) {
        const char* msg = "Unable to load new texture";
        throw GameException(msg, GameException::ABORT);
     }
     SDL_RenderCopy(renderer, textures[this->current_render_state], &this->src_rect, &this->dest_rect);
   // SDL_RenderCopy(renderer, this->anim_texture, &this->src_rect, &this->dest_rect);
}