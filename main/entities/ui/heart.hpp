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
    //
    
    sprite = new CSprite(m_textures["ui/heart.png"]);
    scale=3.5;
    sprite->setPosition(-20, -20);
    // sprite->setOrigin(m_textures["ui/heart.png"].getSize().x/2, m_textures["ui/heart.png"].getSize().y/2); 
}

void HP::update(float time=0)
{
   
}