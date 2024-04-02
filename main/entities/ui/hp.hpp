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

    text = new sf::Text;
    text->setFont(m_fonts["singleday.ttf"]); // font is a sf::Font
    text->setString("HP");
    text->setPosition(0, 0);
    text->setCharacterSize(50); // in pixels, not points!
    text->setFillColor(sf::Color::White);
}

void HP::update(float time=0)
{
    sAnimate();
}