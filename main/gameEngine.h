#include "entityManager.h"
#include <math.h>
#include <string>

// Constants

#define WINDOW_WIDTH sf::VideoMode::getDesktopMode().width
#define WINDOW_HEIGHT 720

class Assets
{
public:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;

    void addTexture(std::string path)
    {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/sprite/" + path))
        {
            std::cout << path << "not found";
        }
        m_textures[path] = texture;
    }

    void addFont(std::string path)
    {

        sf::Font font;
        if (!font.loadFromFile("assets/" + path))
        {
            std::cout << path << "not found";
        }
        m_fonts[path] = font;
    }
};

//
Assets g_assets;
sf::RenderWindow g_window;

class Scenes
{
public:
    EntityManager g_entities;
    virtual void run()
    {
        std::cout << "def";
    };
    virtual void sRender()
    {
    }
};

class Scene_Menu : public Scenes
{
public:
    void run();
    void sRender(std::vector<Entity *> &entites);
};

void Scene_Menu::run()
{
    std::cout << "Menu";
    g_entities.addEntities("Player", 1, 1, g_assets.m_textures["player_idle.png"], true, g_assets.m_fonts["noto.ttf"], "hello world");
    sRender(g_entities.getEntities());
}

void Scene_Menu::sRender(std::vector<Entity *> &entities)
{
    g_window.clear();
    for (auto entity : entities)
    {
        g_window.draw(entity->csprite->sprite);
        if (entity->ctext != NULL)
        {
            g_window.draw(entity->ctext->text);
        }
    }
    g_window.display();
}



class GameEngine
{
    sf::Event events;
    Scenes *currentScene = new Scene_Menu;

    bool is_running;
    int frames;

public:
    GameEngine();
    void run();
    void changeScene(Scenes *scene);
};

GameEngine::GameEngine()
{
    is_running = true;
    frames = 0;
    currentScene = new Scene_Menu();

    g_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    g_window.setFramerateLimit(60);

    g_assets.addTexture("player_idle.png");
    g_assets.addFont("noto.ttf");
}

void GameEngine::run()
{

    currentScene->run();
    currentScene->sRender();

    while (is_running)
    {
        while (g_window.pollEvent(events))
        {
            if (events.type == sf::Event::Closed)
            {
                g_window.close();
                is_running = false;
            }
        }

        frames++;
    }
}

void GameEngine::changeScene(Scenes *scene)
{
    currentScene = scene;
}