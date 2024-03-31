#include "../_Entity.hpp"

#pragma once
class Mana : public Entity
{

public:
    Mana();

    // functions
    void update(float time);
};

Mana::Mana()
{

    tag = "Mana";

    sprite = new CSprite(m_textures["ui/mana.png"]);
    sprite->setOrigin(0, 0);
    scale = 4;
}

void Mana::update(float time = 0)
{
}