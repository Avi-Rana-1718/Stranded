#include "../entities/_Entity.hpp"
#include "../entities/ui/button.hpp"
#include "../entities/ui/crosshair.hpp"

#pragma once

class Scene_Over : public Scenes
{
    //

public:
    Entity *par;

    Entity *crosshair;

    void init();
    void run(float time);
    void update();
    
};

void Scene_Over::init()
{

    Scenes::init();

    par = new Entity;
    par->particles = new ParticleSystem(WINDOW_W, WINDOW_W);
    ui.push_back(par);

    Entity *btn = new Button("Exit", "close");
    btn->text->setPosition(30, WINDOW_H - 100);

    ui.push_back(btn);

    Entity *temp = new Entity;
    temp->text = new sf::Text;
    temp->text->setFont(m_fonts["epilogue.ttf"]); // font is a sf::Font
    temp->text->setString("You died!");
    temp->text->setStyle(sf::Text::Bold);
    temp->text->setCharacterSize(50); // in pixels, not points!
    temp->text->setPosition(30, 30);
    temp->text->setFillColor(sf::Color(240, 237, 237));
    ui.push_back(temp);

    temp = new Entity;
    temp->text = new sf::Text;
    temp->text->setFont(m_fonts["epilogue.ttf"]); // font is a sf::Font
    temp->text->setString("\nWaves survived: " + std::to_string(wave) + "\nEnemies killed: " + std::to_string(score));
    temp->text->setCharacterSize(35); // in pixels, not points!
    temp->text->setPosition(30, 100);
    temp->text->setFillColor(sf::Color(240, 237, 237));
    ui.push_back(temp);

    // crosshair
    crosshair = new Crosshair;
    ui.push_back(crosshair);
}

void Scene_Over::run(float time)
{
    deltaTime = time;

    update();
    sRender();
}

void Scene_Over::update()
{

    par->particles->update(-10, -10);

    // change crosshair position
    crosshair->sprite->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

    for (auto &entity : ui)
    {
        entity->update(deltaTime);
    }

    if (nextScene != NULL)
    {
        currentScene = nextScene;
        currentScene->init();
    }
}