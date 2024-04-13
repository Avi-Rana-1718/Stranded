#include "../_Entity.hpp"

#pragma once
class Energy : public Entity
{

public:
    Energy();

    // functions
    void update(float time);

};

Energy::Energy()
{

    tag="Energy";
    //
    
    sprite = new CSprite(m_textures["ui/energy.png"]);
    scale=3.5;
    sprite->setPosition(-20, -20 + m_textures["ui/heart.png"].getSize().y*scale);
    // sprite->setOrigin(m_textures["ui/heart.png"].getSize().x/2, m_textures["ui/heart.png"].getSize().y/2); 
}

void Energy::update(float time=0)
{
   
}