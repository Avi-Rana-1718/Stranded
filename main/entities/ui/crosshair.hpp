#include "../_Entity.hpp"

#pragma once
class Crosshair : public Entity
{

public:
    Crosshair();

    // functions
    void update(float time);

};

Crosshair::Crosshair()
{

    tag="Crosshair";
    sprite = new CSprite(m_textures["crosshair.png"]);
    sprite->setOrigin(m_textures["crosshair.png"].getSize().x/2, m_textures["crosshair.png"].getSize().y/2);
    scale=0.2;

}

void Crosshair::update(float time=0)
{
    // sAnimate();

    sprite->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}