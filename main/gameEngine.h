#include "entityManager.h"
#include <math.h>
#include <string>

// Constants

const int WINDOW_WIDTH = 1792;
const int WINDOW_HEIGHT = 720;

#define WORLD_SX 4
#define WORLD_SY 4

class Assets
{
public:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
    std::map<std::string, sf::SoundBuffer> m_sounds;

    void addTexture(std::string path)
    {
        sf::Texture texture;
        if (!texture.loadFromFile("assets/sprites/" + path))
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
    void addSound(std::string path)
    {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("assets/audio/" + path))
        {
            std::cout << path << "not found";
        }

        m_sounds[path] = buffer;
    }
};

//

Assets g_assets;
sf::RenderWindow g_window;
sf::Event events;

int frames;

// Scenes

class Scenes
{
public:
    EntityManager g_entities;

    Entity *cursor = NULL;

    virtual void init(){};
    virtual void run(){};

    //
    void sRender(std::vector<Entity *> &entities);

    ~Scenes();
};

Scenes *currentScene = NULL;
void changeScene(Scenes *scene);

void Scenes::sRender(std::vector<Entity *> &entities)
{
    g_window.clear();
    for (auto entity : entities)
    {
        if (entity->ctext != NULL)
        {
            g_window.draw(entity->ctext->text);
        }
        if (entity->cshape != NULL)
        {
            g_window.draw(*entity->cshape);
        }
        g_window.draw(*(entity->csprite));
    }

    if (cursor != NULL)
    {
        g_window.draw(*cursor->csprite);
    }

    g_window.display();
}

Scenes::~Scenes()
{
    g_entities.clearEntities();
}

// Scenes_Play

class Scenes_Play : public Scenes
{
public:
    Entity *player;
    std::map<std::string, std::vector<sf::Texture *>> animationMap;
    void init();
    void run();

    int refFrame = 0;

    // Systems
    void sInput(Entity *player);
    void sMove(std::vector<Entity *> &entities);
    void sAnimate(std::vector<Entity *> &entities);
};

void Scenes_Play::init()
{

    cursor = new Entity("Cursor", -1, g_assets.m_textures["cursor.png"].getSize().x, g_assets.m_textures["cursor.png"].getSize().x, 300, 300, g_assets.m_textures["cursor.png"]);
    cursor->csprite->setScale(sf::Vector2f(1.5, 1.5));

    // background
    for (int i = WINDOW_WIDTH / 2 - 16 * 4 * 7; i < WINDOW_WIDTH / 2 + 16 * 4 * 7; i += 16 * 4)
    {
        for (int j = WINDOW_HEIGHT / 2 - 16 * 4 * 5 + 50; j < WINDOW_HEIGHT / 2 + 16 * 4 * 5 - 50; j += 16 * 4)
        {
            std::string id;

            if (j >= WINDOW_HEIGHT / 2 + 16 * 4 * 4 - 50)
            {
                id = "4";
            }
            else
            {
                id = "0";
            }

            Entity *bg = g_entities.addEntities("Background", g_assets.m_textures["grass/" + id + ".png"]);
            bg->csprite->setPosition(sf::Vector2f(i, j));
        }
    }

    // player
    player = g_entities.addEntities("wizard", g_assets.m_textures["wizard/idle.png"]);
    player->ctransform = new CTransform(5.f, 5.f);
    player->csprite->setPosition(sf::Vector2f(300, 300));
    player->controllable = true;
    player->animated = true;

    //slime
    Entity* slime = g_entities.addEntities("blueSlime", g_assets.m_textures["slime/blue/0.png"]);
    slime->ctransform = new CTransform(1.f,1.f);
    slime->csprite->setPosition(sf::Vector2f(0, 0));
    slime->animated = true;
    slime->stationary = false;

    // animation setup
    animationMap["wizard/move"].push_back(&g_assets.m_textures["wizard/move_1.png"]);
    animationMap["wizard/move"].push_back(&g_assets.m_textures["wizard/move_2.png"]);
    animationMap["wizard/move"].push_back(&g_assets.m_textures["wizard/move_3.png"]);

    animationMap["wizard/attack"].push_back(&g_assets.m_textures["wizard/attack_1.png"]);
    animationMap["wizard/attack"].push_back(&g_assets.m_textures["wizard/attack_2.png"]);
    animationMap["wizard/attack"].push_back(&g_assets.m_textures["wizard/attack_3.png"]);

    animationMap["wizard/idle"].push_back(&g_assets.m_textures["wizard/idle.png"]);

animationMap["blueSlime/move"].push_back(&g_assets.m_textures["slime/blue/1.png"]);
animationMap["blueSlime/move"].push_back(&g_assets.m_textures["slime/blue/2.png"]);
animationMap["blueSlime/move"].push_back(&g_assets.m_textures["slime/blue/3.png"]);
    animationMap["blueSlime/idle"].push_back(&g_assets.m_textures["slime/blue/0.png"]);
}

void Scenes_Play::run()
{
    sInput(player);
    sRender(g_entities.getEntities());
    sMove(g_entities.getEntities());
    sAnimate(g_entities.getEntities());
}

void Scenes_Play::sInput(Entity *player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player->getTop() > 0)
    {
        player->csprite->move(0, -player->ctransform->speedY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player->getBottom() < WINDOW_HEIGHT)
    {
        player->csprite->move(0, player->ctransform->speedY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player->getLeft() > 0)
    {
        player->csprite->move(-player->ctransform->speedX, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player->getRight() < WINDOW_WIDTH)
    {
        player->csprite->move(player->ctransform->speedX, 0);
    }
}

void Scenes_Play::sMove(std::vector<Entity *> &entities)
{
    for (auto entity : entities)
    {
        if (entity->controllable == false && entity->stationary == false && entity->ctransform != NULL)
        {
            entity->isMoving=true;
            if(entity->csprite->getPosition().x  > player->csprite->getPosition().x) {
            entity->csprite->move(-entity->ctransform->speedX, 0);
            } else if(entity->csprite->getPosition().x < player->csprite->getPosition().x) {
            entity->csprite->move(entity->ctransform->speedX, 0);
            }

                        if(entity->csprite->getPosition().y  > player->csprite->getPosition().y) {
            entity->csprite->move(0, -entity->ctransform->speedY);
            } else if(entity->csprite->getPosition().y < player->csprite->getPosition().y) {
            entity->csprite->move(0, entity->ctransform->speedY);
            }
        }
    }

    cursor->csprite->setPosition(sf::Mouse::getPosition(g_window).x, sf::Mouse::getPosition(g_window).y);
}

void Scenes_Play::sAnimate(std::vector<Entity *> &entities)
{

    for (auto entity : entities)
    {
        if (entity->animated)
        {
            entity->sAnimate(animationMap, frames);
        }
    }
}
// GameEngine

class GameEngine
{
    std::vector<sf::VideoMode> fullscreenModes;

    bool is_running;

public:
    GameEngine();
    void run();
};

GameEngine::GameEngine()
{
    is_running = true;
    frames = 0;

    changeScene(new Scenes_Play);

    fullscreenModes = sf::VideoMode::getFullscreenModes();

    g_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bad FlappyBird");
    g_window.setFramerateLimit(60);
    g_window.setMouseCursorVisible(false);

    // Load assets
    g_assets.addTexture("cursor.png");

    g_assets.addTexture("grass/0.png");
    g_assets.addTexture("grass/1.png");
    g_assets.addTexture("grass/2.png");
    g_assets.addTexture("grass/3.png");
    g_assets.addTexture("grass/4.png");
    g_assets.addTexture("grass/5.png");

    g_assets.addTexture("wizard/idle.png");
    g_assets.addTexture("wizard/move_1.png");
    g_assets.addTexture("wizard/move_2.png");
    g_assets.addTexture("wizard/move_3.png");

    g_assets.addTexture("wizard/attack_1.png");
    g_assets.addTexture("wizard/attack_2.png");
    g_assets.addTexture("wizard/attack_3.png");

    g_assets.addTexture("slime/blue/0.png");
    g_assets.addTexture("slime/blue/1.png");
    g_assets.addTexture("slime/blue/2.png");
    g_assets.addTexture("slime/blue/3.png");

    // g_assets.addFont("noto.ttf");
}

void GameEngine::run()
{
    currentScene->init();
    while (is_running)
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            g_window.create(fullscreenModes[0], "Bad FlappyBird");
        }

        currentScene->run();
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

void changeScene(Scenes *scene)
{
    delete currentScene;
    currentScene = scene;
}