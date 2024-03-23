#include "../_Entity.hpp"

#pragma once
class BronzeVase : public Entity
{

public:
    BronzeVase();

    // functions
    void update(float time);

};

BronzeVase::BronzeVase()
{

    tag="bronzeVase";

    lastActionFrame = -1;
    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    //
    animationMap["idle"].push_back(m_textures["interactables/bronzeVase/idle.png"]);
    animationMap["hit"].push_back(m_textures["interactables/bronzeVase/hit.png"]);


    sprite = new CSprite(m_textures["interactables/bronzeVase/idle.png"]);
    sprite->setPosition(0, 720-75);
    scale=3;
}

void BronzeVase::update(float time)
{
    sAnimate();
}