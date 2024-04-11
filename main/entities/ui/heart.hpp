#include "../_Entity.hpp"

#pragma once
class Heart : public Entity
{

public:
    Heart();

    // functions
    void update(float time);
};

Heart::Heart()
{

    tag = "Heart";

    sprite = new CSprite(m_textures["ui/heart.png"]);
    sprite->setOrigin(0, 0);
    sprite->setPosition(0, 0);
    scale = 4;
}

void Heart::update(float time = 0)
{
}