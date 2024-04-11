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
    // animationMap["idle"].push_back(m_textures["ui/mp.png"]);

    text = new sf::Text;
    text->setFont(m_fonts["singleday.ttf"]); // font is a sf::Font
    text->setString("MP");
    text->setPosition(20, 55);
    text->setCharacterSize(50); // in pixels, not points!
    text->setFillColor(sf::Color::White);
}

void MP::update(float time=0)
{
    
}