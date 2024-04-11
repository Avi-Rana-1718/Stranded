#include "../entities/_Entity.hpp"

#include "../entities/ui/button.hpp"
#include "../entities/bg/map.hpp"

#pragma once

class Scene_Menu : public Scenes
{
public:
    //

    void init();
    void run(float time);
    void update();
    // systems
};

void Scene_Menu::init()
{
    Scenes::init();

    window.setMouseCursorVisible(true);
    Entity* temp = new Button("Start", "Scene_Play");
    temp->text->setPosition(50, WINDOW_H/2);
    ui.push_back(temp);

    Entity* temp2 = new Button("Credits", "Scene_Credits");
    temp2->text->setPosition(50, WINDOW_H/2 + 80);
    ui.push_back(temp2);


    // Entity* temp3 = new Button("Credits", "Scene_Credits");
    // temp3->text->setPosition(50, WINDOW_H/2 + 160);
    // ui.push_back(temp3);


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
}