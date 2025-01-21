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


std::map<std::string, AnimationAsset::texture_data> AnimationAsset::get_anim_textures() {
    return this->anim_textures;
}

void AnimationAsset::add_anim_texture(std::string anim_name, SDL_Texture* texture,  int number_of_frames) {
    //this->anim_textures[anim_name] = texture;
    texture_data data = {this->texture_paths[anim_name].path, number_of_frames, texture};
    this->anim_textures[anim_name] = data;
}


// @deprecated
void AnimationAsset::set_num_frames(int num_frames) {
    this->num_frames = num_frames;
}

void AnimationAsset::add_texture_path(std::string name, std::string path, int number_of_frames) {
   
    texture_data data = {path, number_of_frames};
    this->texture_paths[name] = data;


}

const std::map<std::string, AnimationAsset::texture_data> AnimationAsset::get_texture_paths() {
    return this->texture_paths;
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


SDL_Rect AnimationAsset::get_previous_dest_rect() {
    return this->previous_dest_rect;
}

void AnimationAsset::set_previous_dest_rect(SDL_Rect dest_rect) {
    this->previous_dest_rect = dest_rect;
}

void AnimationAsset::set_render_state(const std::string& state) {
    this->current_render_state = state;
}

const std::string& AnimationAsset::get_render_state() {
    return this->current_render_state;
}


void AnimationAsset::load_textures(SDL_Renderer* renderer) {
    for (auto texture_path : this->texture_paths) {
        SDL_Surface* loaded_surface = IMG_Load(texture_path.second.path.c_str());
        SDL_Texture* new_texture = nullptr;
        if (!loaded_surface) {
            const char* msg =  "Unable to load image";
            std::cerr << texture_path.second.path << "! SDL_image Error: " << IMG_GetError() << std::endl;
            throw GameException(msg, GameException::ABORT);
        }

        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        SDL_FreeSurface(loaded_surface);
        if (!new_texture) {
            const char* msg = "Unable to load new texture";
            throw GameException(msg, GameException::ABORT);
        }

        this->add_anim_texture(texture_path.first, new_texture, texture_path.second.number_of_frames); 
    }
}

/**
 * // TODO - calll UPDATE only when the dest rect is different than before??
 * 
 * 
 * 
 * TODO understand the frame time handling. 
 * if we set the last frame time from multiple update calls, this can cause the animation to be faster than expected.
 */
void AnimationAsset::update() {
    Uint32 current_time = SDL_GetTicks();
    std::map<std::string, AnimationAsset::texture_data> textures = this->get_anim_textures();
    this->set_previous_dest_rect(this->get_dest_rect()); // Store the previous dest rect
    if (current_time - this->last_frame_time > FRAME_TIME) {
        current_frame = (current_frame + 1) %  textures[this->current_render_state].number_of_frames;             // @TODO - instead of 6 - use the number of frame from the current TEXTURE PATH
        this->src_rect.x = current_frame * (this->src_rect.w + 28);        // @TODO move to a var 28 is the offset of the sprite!
        this->last_frame_time = current_time;
    }
}


void AnimationAsset::render(SDL_Renderer* renderer) {
     std::map<std::string, AnimationAsset::texture_data> textures = this->get_anim_textures();
     if (textures.find(this->current_render_state) == textures.end()) {
        const char* msg = "Unable to load new texture";
        throw GameException(msg, GameException::ABORT);
     }

     // TEST WE Render the idle until it changes
    SDL_RenderCopy(renderer, textures[this->current_render_state].texture, &this->src_rect, &this->dest_rect);
}