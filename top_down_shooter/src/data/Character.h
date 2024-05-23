#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

struct Weapon
{
    std::string name;
    float damage = 1.0f;
};

class Character
{
  public:
    static std::vector<Weapon> &get_weapons();

  private:
    static std::vector<Weapon> weapons_;
};
#endif
