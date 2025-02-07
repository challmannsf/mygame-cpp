#pragma once

#include <iostream>
#include "CombatSkill.h"


class CombatSystem {

    private:
        std::vector<CombatSkill> skills;

    public:
        CombatSystem();
        ~CombatSystem();

        void add_skill(CombatSkill skill);

};