#include "../_Entity.hpp"
#include "../../scenes/Scenes.hpp"

#pragma once
class Button : public Entity
{

public:
    std::string action;

    Button(std::string label, std::string scene);

    // functions
    void update(float time);
    void listen();

};

Button::Button(std::string label, std::string scene)
{

    tag="Button";

    action = scene;

    //
    sprite = new CSprite(m_textures["ui/bar_blue_mid.png"]);
    sprite->setPosition(sf::Vector2f(WINDOW_W/2, WINDOW_H/2));
    sprite->setOrigin(m_textures["ui/bar_blue_mid.png"].getSize().x/2, m_textures["ui/bar_blue_mid.png"].getSize().y/2);
    scale=10;

    text = new sf::Text;
    text->setFont(m_fonts["noto.ttf"]); // font is a sf::Font
    text->setString("Button");
    text->setPosition(sprite->getPosition().x-24, sprite->getPosition().y-24);
    text->setCharacterSize(24); // in pixels, not points!
    text->setFillColor(sf::Color::White);

}

void Button::update(float time=0)
{
    sAnimate();
    listen();
}

void Button::listen() {
    if(sprite->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        Scenes* temp = currentScene;
        if(action=="Scene_Play") {
        currentScene =  new Scene_Play;
        }
        delete temp;
    }
}