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
    sprite->setPosition(-20, -20);
    // sprite->setOrigin(m_textures["ui/heart.png"].getSize().x/2, m_textures["ui/heart.png"].getSize().y/2); 
    scale=4;
}

void HP::update(float time=0)
{
   
}