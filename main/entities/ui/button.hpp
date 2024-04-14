#include "../_Entity.hpp"
#include "../../scenes/Scenes.hpp"

#pragma once
class Button : public Entity
{

public:
    std::string action;
    bool isClicked;

    Button(std::string label, std::string scene);
    ~Button();

    // functions
    void update(float time);
    void listen();
    void decideAction();
};

Button::Button(std::string label, std::string scene)
{
    tag = "Button";
    isClicked = false;

    action = scene;

    text = new sf::Text;
    text->setFont(m_fonts["epilogue.ttf"]);
    text->setString(label);
    text->setPosition(0, 0);
    text->setCharacterSize(50);
    text->setFillColor(sf::Color::White);
}

void Button::update(float time = 0)
{
    decideAction();
    listen();
}

void Button::listen()
{

    // hover text change
    if (text->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
    {
        text->setFillColor(sf::Color(128, 128, 128));
    }
    else
    {
        text->setFillColor(sf::Color(255, 255, 255));
    }

    // click
    if (text->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && isClicked == false)
    {

        isClicked = true;

        if (action == "p_inc_dmg")
        {
            spawn = true; // enemy/wave spawn set true
            playerProps.projectileDamage++;
            sound.setBuffer(m_sounds["upgrade.wav"]);
            sound.play();
            return;
        } else if(action == "p_inc_ph") {
            spawn=true;
            playerProps.projectileHealth++;
            sound.setBuffer(m_sounds["upgrade.wav"]);
            sound.play();
            return;
        } else if (action == "p_inc_pf") {
            spawn=true;
            playerProps.projectileFirerate-=0.1;
            sound.setBuffer(m_sounds["upgrade.wav"]);
            sound.play();
            return;
        }
        else if (action == "Scene_Play" || action == "Scene_Credits" || action == "Scene_Menu")
        {
            if (action == "Scene_Play")
            {
                // delete currentScene;
                currentScene = scenes["play"];
            }
            else if (action == "Scene_Menu")
            {
                currentScene = scenes["menu"];
            }
            else if (action == "Scene_Credits")
            {
                currentScene = scenes["credits"];
            }

            currentScene->init();
        } else if (action=="close") {
            window.close();
            isRunning=false;
        }
        else
        {
            std::cout << "ERROR: Unregistered Action" << std::endl;
        }
            sound.setBuffer(m_sounds["select.wav"]);
            sound.play();
    }
}

void Button::decideAction() {
        if(text->getString()=="incPD") {
            text->setString("INC DMG");
            action="p_inc_dmg";
            isClicked=false;
        } else if (text->getString()=="incPH") {
            text->setString("INC PH");
            action="p_inc_ph";
            isClicked=false;
        } else if (text->getString()=="incPF") {
            text->setString("INC PF");
            action="p_inc_pf";
            isClicked=false;
        }
}

Button::~Button()
{
    delete text;
}