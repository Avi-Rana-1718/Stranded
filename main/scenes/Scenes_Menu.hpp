#include "../entities/_Entity.hpp"
#include "./Scenes_Play.hpp"

#include "../entities/ui/button.hpp"
#include "../entities/bg/map.hpp"

#pragma once

class Scene_Menu : public Scenes
{
public:

    

    Entity* start;

    //

    Scene_Menu();

    void run(float time);
    void update();
    // systems
};

Scene_Menu::Scene_Menu()
{
    ui.push_back(new Button("Start", "Scene_Play"));
    // ui.push_back(new Background);
}

void Scene_Menu::run(float time)
{
    deltaTime = time;

    update();
    sRender();
    
}

void Scene_Menu::update()
{

    for(auto& entity : ui) {
        entity->update(deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        currentScene=new Scene_Play;
    }
}