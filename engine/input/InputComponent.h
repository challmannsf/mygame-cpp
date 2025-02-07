#pragma once

#include "../Component.h"
#include "../character/Player.h"

// Forward declaration of GameWorld class
class Player;

class InputComponent : public Component {

    private:
        Player* player;

    public:
        InputComponent();
        ~InputComponent();

        void set_player(Player* player);
        void handle_input(SDL_Event event);
};