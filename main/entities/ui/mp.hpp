#include "../_Entity.hpp"

#pragma once
class MP : public Entity
{

public:
    MP();

    // functions
    void update(float time);

};

MP::MP()
{

    tag="MP";

    lastActionFrame = -1;
    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    //
    animationMap["idle"].push_back(m_textures["ui/mp.png"]);

    sprite = new CSprite(m_textures["ui/mp.png"]);
    sprite->setPosition(0, m_textures["ui/hp.png"].getSize().y*4);
    sprite->setOrigin(0, 0);
    scale=4;
}

void MP::update(float time=0)
{
    sAnimate();
}