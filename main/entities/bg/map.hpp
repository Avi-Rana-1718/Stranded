#include "../_Entity.hpp"

#pragma once
class Background : public Entity
{

public:
    Background();

    // functions
    void update(float time);

};

Background::Background()
{

    tag="Background";

    //

    sprite = new CSprite(m_textures["map.png"]);
    sprite->setOrigin(m_textures["map.png"].getSize().x/2, m_textures["map.png"].getSize().y/2);
    sprite->setPosition(sf::Vector2f(1800/2,720/2));
    scale=4.5;
}

void Background::update(float time)
{
}