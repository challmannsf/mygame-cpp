#include "AnimationAsset.h"



AnimationAsset::AnimationAsset() {
    this->last_frame_time = SDL_GetTicks();
}
AnimationAsset::~AnimationAsset() {}

void AnimationAsset::set_anim_texture(SDL_Texture* texture) {
    this->anim_texture = texture;
}

SDL_Texture* AnimationAsset::get_anim_texture() {
    return this->anim_texture;
}

void AnimationAsset::set_num_frames(int num_frames) {
    this->num_frames = num_frames;
}

void AnimationAsset::set_texture_path(std::string path) {
    this->texture_path = path;
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

void AnimationAsset::load_texture(SDL_Renderer* renderer) {

    SDL_Texture* new_texture = nullptr;
    SDL_Surface* loaded_surfcace = IMG_Load(this->get_texture_path().c_str());
    if (!loaded_surfcace) {
        const char* msg =  "Unable to load image";
        std::cerr << this->get_texture_path() << "! SDL_image Error: " << IMG_GetError() << std::endl;
        throw GameException(msg, GameException::ABORT);
    }

    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surfcace);
    SDL_FreeSurface(loaded_surfcace);
    if (!new_texture) {
        const char* msg =  "Unable to load new texture";
        throw GameException(msg, GameException::ABORT);
    }

    this->set_anim_texture(new_texture);
}

/**
 * TODO understand the frame time handling. 
 * if we set the last frame time from multiple update calls, this can cause the animation to be faster than expected.
 */
void AnimationAsset::update() {
    Uint32 current_time = SDL_GetTicks();
    if (current_time - this->last_frame_time > FRAME_TIME) {
        current_frame = (current_frame + 1) % this->num_frames; // Cycle through frames
        this->src_rect.x = current_frame * (this->src_rect.w + 28);        // 28 is the offset of the sprite!
        this->last_frame_time = current_time;
    }
}


void AnimationAsset::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, this->anim_texture, &this->src_rect, &this->dest_rect);
}