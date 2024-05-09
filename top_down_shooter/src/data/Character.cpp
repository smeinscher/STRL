#include "Character.h"

std::vector<Weapon> Character::weapons_ = {{"fists", 1.0f}, {"bow", 5.0f}};

std::vector<Weapon> &Character::get_weapons()
{
    return weapons_;
}
