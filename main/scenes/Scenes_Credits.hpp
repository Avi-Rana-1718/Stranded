#include "../entities/_Entity.hpp"
#include "../entities/ui/button.hpp"

#pragma once

class Scene_Credits : public Scenes
{
    //
public:
    void init();
    void run(float time);
    void update();
    // systems
};

void Scene_Credits::init()
{

    Scenes::init();

    Entity *btn = new Button("Back", "Scene_Menu");
    btn->text->setPosition(30, WINDOW_H - btn->text->getGlobalBounds().getSize().y - 30);
    btn->text->setCharacterSize(30);
    ui.push_back(btn);

    Entity *temp = new Entity;
    temp->text = new sf::Text;
    temp->text->setFont(m_fonts["epilogue.ttf"]); // font is a sf::Font
    temp->text->setString("Credits");
    temp->text->setStyle(sf::Text::Bold);
    temp->text->setCharacterSize(40); // in pixels, not points!
    temp->text->setPosition(30, 30);
    temp->text->setFillColor(sf::Color(240, 237, 237));
    ui.push_back(temp);

    temp = new Entity;
    temp->text = new sf::Text;
    temp->text->setFont(m_fonts["epilogue.ttf"]); // font is a sf::Font
    temp->text->setString("A 2D top-down survival game made in C++ with SFML!\n\n Made by\n - Avi Rana (2211981115)\n - Ayush Dogra (2211981119)\n - Arnav Gupta (2211981092)\n - Akshit Mehta (2211981043)\n\nMusic: DOS-88 - Crash Landing");
    temp->text->setCharacterSize(35); // in pixels, not points!
    temp->text->setPosition(30, 100);
    temp->text->setFillColor(sf::Color(240, 237, 237));
    ui.push_back(temp);
}

void Scene_Credits::run(float time)
{
    deltaTime = time;

    update();
    sRender();
}

void Scene_Credits::update()
{

    for (auto &entity : ui)
    {
        entity->update(deltaTime);
    }

    if (nextScene != NULL)
    {
        currentScene = nextScene;
        nextScene = NULL;
        currentScene->init();
    }
}
