#include "gameEngine.h"

class GameEngine;

class Scene_menu : public Scenes
{
public:
    Entity *player;
    void init();

    void update();

    // systems
    void sRender();
    void sdoAction();
};
void Scene_Menu::Scene_Menu(GameEngine* ptr) : Scenes(ptr);

void Scene_menu::init()
{
    std::cout << "menu";
}

class Scene_play : public Scenes
{
public:
    Entity *player;
    void init();
    void update();

    // systems
    void sRender(std::vector<Entity *> entities);
    void sdoAction();
};
void Scene_play::Scene_play(GameEngine* ptr) : Scenes(ptr);
void Scene_play::init()
{
    std::cout << "play";
    g_entities.addEntities("Player", 1, 1, g_assets.m_textures["player_idle"]);
}

void Scene_play::update() {
    sRender(g_entities.getEntities());
}

void Scene_play::sRender(std::vector<Entity *> entities) {

    for(auto entity : entities) {
    g_window.clear();
    g_window.draw(entity);
    g_window.display();
    }

}