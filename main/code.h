#include "entityManager.h"
#include <math.h>
#include <string>

// Constants

#define WINDOW_WIDTH sf::VideoMode::getDesktopMode().width
#define WINDOW_HEIGHT 720

sf::Font font;

class Assets
{
public:
    std::map<std::string, sf::Texture> m_textures; // map
    std::map<std::string, Animation> m_animations;
    std::map<std::string, sf::Sound> m_sounds;
    std::map<std::string, sf::Font> m_fonts;

    void addTexture(std::string path);
    void addAnimation(std::string path);
    void addSound(std::string path);
    void addFont(std::string path);

    sf::Texture getTexture();
    Animation getAnimation();
    sf::Sound getSound();
    sf::Font getFont();
};

class Action
{

    std::string m_name = "NONE";
    std::string m_type = "NONE";

public:
    Action()
    {
        m_name = "NONE";
        m_type = "NONE";
    }
    Action(const std::string &name, const std::string &type)
    {
        m_name = name;
        m_type = type;
    };

    std::string name()
    {
        return m_name;
    };
    std::string type()
    {
        return m_type;
    };
};

class GameEngine
{
public:
    sf::RenderWindow g_window;
    sf::Event event;

    std::map<std::string, Scenes> scenes;
    std::map<sf::Keyboard, std::string> actions;
    Assets m_assets;

    Scenes* currentScene;

    int frames;
    bool is_running;

    void changeScene(std::string scene);

    GameEngine()
    {
        g_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
        g_window.setFramerateLimit(60);
        init();
    }

    void init();
    void run();
    void quit();
    void SUserInput();

    void init()
    {
        is_running = true;
        frames = 0;
        currentScene = new Scene_play;
    }

    void run()
    {
        init();
        while (is_running)
        {
            currentScene->sRender();
            frames++;
        }
    }

    void quit()
    {
        is_running = false;
    }
};

class Scenes
{
public:
    EntityManager g_entities;
    Action action;
    void init();
    void update();
    void sRender();
    void sdoAction();
};

class Scene_play : Scenes
{
public:
    Entity *player;

    void init()
    {
        registerAction(sf::Keyboard::W, "UP");
    }

    void sdoAction()
    {
        if (action.type() == "START")
        {
            if (action.name() == "UP")
            {
            }
            else if (action.name() == "DOWN")
            {
            }
            else if (action.name() == "RIGHT")
            {
            }
            else if (action.name() == "LEFT")
            {
            }
        }
    }
};