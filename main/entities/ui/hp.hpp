#include "../_Entity.hpp"

#pragma once
class HP : public Entity
{

public:
    HP();

    // functions
    void update(float time);

};

HP::HP()
{

    tag="HP";

    lastActionFrame = -1;
    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    //
    animationMap["idle"].push_back(m_textures["ui/hp.png"]);

    sprite = new CSprite(m_textures["ui/hp.png"]);
    sprite->setPosition(0, 0);
    sprite->setOrigin(0, 0);
    scale=4;
}

void HP::update(float time=0)
{
    sAnimate();
}