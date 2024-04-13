#include "../entities/_Entity.hpp"

#include "../entities/ui/button.hpp"
#include "../entities/bg/map.hpp"

#pragma once

class Scene_Menu : public Scenes
{
public:
    //
    Entity *par;

    void init();
    void run(float time);
    void update();

    ~Scene_Menu();
    // systems
};

void Scene_Menu::init()
{

    Scenes::init();
    window.setMouseCursorVisible(true);


    Entity* title = new Entity;
    title->text = new sf::Text;
    title->text->setFont(m_fonts["technicality1.ttf"]);
    title->text->setCharacterSize(80);
    title->text->setFillColor(sf::Color::White);
    title->text->setString("STRANDED");
    title->text->setPosition(50, WINDOW_H/2-200);
    ui.push_back(title);

    Entity* temp = new Button("Start", "Scene_Play");
    temp->text->setPosition(50, WINDOW_H/2);
    ui.push_back(temp);

    Entity* temp2 = new Button("Credits", "Scene_Credits");
    temp2->text->setPosition(50, WINDOW_H/2 + 80);
    ui.push_back(temp2);

    temp2 = new Button("Exit", "close");
    temp2->text->setPosition(50, WINDOW_H/2 + 160);
    ui.push_back(temp2);


    Entity* ship = new Entity;
    ship->sprite = new CSprite(m_textures["ship.png"]);
    ship->scale=5;
    ship->sprite->setPosition(WINDOW_W-ship->sprite->getGlobalBounds().getSize().x*ship->scale-100, WINDOW_H/2);
    ui.push_back(ship);

    temp = new Entity;
    temp->text = new sf::Text;
    temp->text->setFont(m_fonts["epilogue.ttf"]);
    temp->text->setCharacterSize(30);
    temp->text->setFillColor(sf::Color::White);
    temp->text->setString("Version 1.0");
    temp->text->setPosition(10, WINDOW_H - 20 - temp->text->getGlobalBounds().getSize().y);
    ui.push_back(temp);

    temp = new Entity;
    temp->text = new sf::Text;
    temp->text->setFont(m_fonts["epilogue.ttf"]);
    temp->text->setCharacterSize(20);
    temp->text->setFillColor(sf::Color::White);
    temp->text->setString("Resolution: " + std::to_string(WINDOW_W) + "x" + std::to_string(WINDOW_H) + "\nTarget FPS: 144");
    temp->text->setPosition(WINDOW_W- 10 - temp->text->getGlobalBounds().getSize().x, 10);
    ui.push_back(temp);

    par = new Entity;
    par->particles = new ParticleSystem(WINDOW_W, WINDOW_W);
    ui.push_back(par);


    par->particles->update(0, 0);

}

void Scene_Menu::run(float time)
{
    deltaTime = time;

    update();
    sRender();


    par->particles->update(0, 0); 
}

void Scene_Menu::update()
{

    for(auto& entity : ui) {
        entity->update(deltaTime);
    }
}

Scene_Menu::~Scene_Menu() {
    delete par;
}