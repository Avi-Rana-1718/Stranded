#include "entityManager.h"
#include <math.h>
#include <string>

// Constants

#define WINDOW_WIDTH 1792
#define WINDOW_HEIGHT 720

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
    void init();
    void run();

    int refFrame = 0;

    // Systems
    void sInput(Entity *player);
    void sMove(std::vector<Entity *> &entities);
    void sAnimate(Entity *player);
};

void Scenes_Play::init()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Entity *bg = g_entities.addEntities("Background", g_assets.m_textures["grass/0.png"]);
            bg->csprite->setPosition(sf::Vector2f(100 + 16 * i * 4, 100 + (bg->h / 2) + 16 * 4 * j));
        }
    }

    player = g_entities.addEntities("Player", g_assets.m_textures["wizard/idle.png"]);
    player->ctransform = new CTransform;
    player->ctransform->speedX = 7.f;
    player->ctransform->speedY = 7.f;
    player->csprite->setPosition(sf::Vector2f(300, 300));
    player->controllable = true;
}

void Scenes_Play::run()
{
    sInput(player);
    sRender(g_entities.getEntities());
    sMove(g_entities.getEntities());
    sAnimate(player);
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

    // melee
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    // {
    //     std::vector<Entity *> entities = g_entities.getEntities();
    //     for (auto entity : entities)
    //     {
    //         if (sword->csprite->getGlobalBounds().intersects(entity->csprite->getGlobalBounds()) && player->e_id != entity->e_id)
    //         {
    //             entity->csprite->move(sword->cweapons->forceX * (signbit(player->ctransform->speedX) ? -1 : 1), sword->cweapons->forceY * (signbit(player->ctransform->speedY) ? -1 : 1));
    //             entity->csprite->setColor(sf::Color::Red);
    //         }
    //     }
    // }
}

void Scenes_Play::sMove(std::vector<Entity *> &entities)
{
    for (auto entity : entities)
    {
        if (entity->controllable == false && entity->stationary == false && entity->ctransform != NULL)
        {
            entity->csprite->move(entity->ctransform->speedX, entity->ctransform->speedY);
        }
    }
}

void Scenes_Play::sAnimate(Entity *player)
{


    bool isMoving = (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D));
    bool isAttacking = false;
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        isAttacking=true;
        player->csprite->setTexture(g_assets.m_textures["wizard/attack_1.png"]);
    } else {
        isAttacking=false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->direction = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->direction = 1;
    }
    player->csprite->setScale(sf::Vector2f(player->direction * player->scale, player->scale));

    if (isMoving && frames >= player->animationTimer + player->animationDelay && player->currentFrame < 3 && !isAttacking)
    {
        player->currentFrame++;
        player->csprite->setTexture(g_assets.m_textures["wizard/move_" + std::to_string(player->currentFrame) + ".png"]);
        player->animationTimer = frames;

        if (player->currentFrame == 3)
        {
            player->currentFrame = 0;
        }
    }
    else if (!isMoving && !isAttacking)
    {
        player->currentFrame = 0;
        player->csprite->setTexture(g_assets.m_textures["wizard/idle.png"]);
        player->animationTimer = 0;
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

    // Load assets
    g_assets.addTexture("grass/0.png");

    g_assets.addTexture("wizard/idle.png");
    g_assets.addTexture("wizard/move_1.png");
    g_assets.addTexture("wizard/move_2.png");
    g_assets.addTexture("wizard/move_3.png");
        g_assets.addTexture("wizard/attack_1.png");

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