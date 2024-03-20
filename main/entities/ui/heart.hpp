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

    tag="Heart";

    lastActionFrame = -1;
    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    //
    animationMap["idle"].push_back(m_textures["ui/heart.png"]);

    sprite = new CSprite(m_textures["ui/heart.png"]);
    sprite->setPosition(0, 720-75);
    scale=3;
}

void Heart::update(float time)
{
    sAnimate();
}