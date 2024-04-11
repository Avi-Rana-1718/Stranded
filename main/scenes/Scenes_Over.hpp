#include "../entities/_Entity.hpp"
#include "../entities/ui/button.hpp"

#pragma once


class Scene_Over : public Scenes {
        //
public:
 
    void init();
    void run(float time);
    void update();
    // systems
};

void Scene_Over::init() {

    Scenes::init();

    Entity* btn = new Button("Try again?", "Scenes_Play");
    btn->text->setPosition(10, 40);
    ui.push_back(btn);

    Entity* temp = new Entity;
    temp->text = new sf::Text;
    temp->text->setFont(m_fonts["epilogue.ttf"]); // font is a sf::Font
    temp->text->setString("You died!");
    temp->text->setStyle(sf::Text::Bold);
    temp->text->setCharacterSize(50); // in pixels, not points!
    temp->text->setPosition(10, 10);
    temp->text->setFillColor(sf::Color(240, 237, 237));
    ui.push_back(temp);

   temp = new Entity;
    temp->text = new sf::Text;
    temp->text->setFont(m_fonts["epilogue.ttf"]); // font is a sf::Font
    temp->text->setString("A 2D top-down survival game made in C++ with SFML!\n\n Made by\n - Avi Rana (2211981115)\n - Ayush Dogra (2211981119)\n - Arnav Gupta (2211981092)\n - Akshit Mehta");
    temp->text->setCharacterSize(35); // in pixels, not points!
    temp->text->setPosition(10, 100);
    temp->text->setFillColor(sf::Color(240, 237, 237));
    ui.push_back(temp);

}

void Scene_Over::run(float time)
{
    deltaTime = time;

    update();
    sRender();
    
}

void Scene_Over::update()
{

    for(auto& entity : ui) {
        entity->update(deltaTime);
    }
}