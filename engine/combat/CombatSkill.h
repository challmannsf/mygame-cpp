#pragma once

#include <iostream>


class CombatSkill {
    private:
        /* data */
    public:
        void attack() {
            std::cout << "Attacking" << std::endl;
        }

        void defend() {
            std::cout << "Defending" << std::endl;
        }

        void cast_spell() {
            std::cout << "Casting spell" << std::endl;
        }
};

