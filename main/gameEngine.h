#include "entityManager.h"
#include "assets.h"
#include <math.h>
#include <string>

// Constants

const int WINDOW_WIDTH = 1792;
const int WINDOW_HEIGHT = 720;

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
    void sAttack(Entity *player);

    void sPhysics(std::vector<Entity *> &entities);
};

void Scenes_Play::init()
{

    cursor = new Entity("Cursor", -1, g_assets.m_textures["cursor.png"].getSize().x, g_assets.m_textures["cursor.png"].getSize().x, 300, 300, g_assets.m_textures["cursor.png"], 3);
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

            Entity *bg = g_entities.addEntities("Background", g_assets.m_textures["grass/" + id + ".png"], 0);
            bg->csprite->setPosition(sf::Vector2f(i, j));
        }
    }

    // player
    player = g_entities.addEntities("wizard", g_assets.m_textures["wizard/idle.png"]);
    player->ctransform = new CTransform(5.5, 5.5);
    player->csprite->setPosition(sf::Vector2f(300, 300));
    player->controllable = true;
    player->animated = true;
    player->e_health = 3;

    // slime
    for (int i = 0; i < 5; i++)
    {
        Entity *slime = g_entities.addEntities("blueSlime", g_assets.m_textures["slime/blue/0.png"]);
        slime->ctransform = new CTransform(1.2f, 1.2f);
        slime->csprite->setPosition(sf::Vector2f(std::rand() % (1500 - 100 + 1) + 100, std::rand() % (700 - 100 + 1) + 100));
        slime->e_health=5;
        slime->animated = true;
        slime->stationary = false;
        slime->isHostile = true;
    }

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
        animationMap["blueSlime/hurt"].push_back(&g_assets.m_textures["slime/blue/3.png"]);
            animationMap["blueSlime/hurt"].push_back(&g_assets.m_textures["slime/blue/4.png"]);

    animationMap["blueSlime/idle"].push_back(&g_assets.m_textures["slime/blue/0.png"]);
}

void Scenes_Play::run()
{
    sInput(player);
    sRender(g_entities.getEntities());
    sMove(g_entities.getEntities());
    sAttack(player);
    sAnimate(g_entities.getEntities());
    sPhysics(g_entities.getEntities());
}

void Scenes_Play::sInput(Entity *player)
{
    player->isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player->getTop() > 0)
    {
        player->csprite->move(0, -player->ctransform->speedY);
        player->isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player->getBottom() < WINDOW_HEIGHT)
    {
        player->csprite->move(0, player->ctransform->speedY);
        player->isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player->getLeft() > 0)
    {
        player->csprite->move(-player->ctransform->speedX, 0);
        player->isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player->getRight() < WINDOW_WIDTH)
    {
        player->csprite->move(player->ctransform->speedX, 0);
        player->isMoving = true;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && frames >= player->animationTimer + 15)
    {
        player->isAttacking = true;
    }
}

void Scenes_Play::sMove(std::vector<Entity *> &entities)
{
    for (auto entity : entities)
    {
        if (entity->controllable == false && entity->stationary == false && entity->ctransform != NULL && entity->isHostile)
        {
            entity->isMoving = true;
            if (entity->csprite->getPosition().x > player->csprite->getPosition().x)
            {
                entity->csprite->move(-entity->ctransform->speedX, 0);
            }
            else if (entity->csprite->getPosition().x < player->csprite->getPosition().x)
            {
                entity->csprite->move(entity->ctransform->speedX, 0);
            }

            if (entity->csprite->getPosition().y > player->csprite->getPosition().y)
            {
                entity->csprite->move(0, -entity->ctransform->speedY);
            }
            else if (entity->csprite->getPosition().y < player->csprite->getPosition().y)
            {
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

void Scenes_Play::sAttack(Entity *player)
{
    if (player->isAttacking && frames >= player->animationTimer + 15)
    {
        std::cout << g_entities.m_totalEntities << std::endl;

        Entity *b = g_entities.addEntities("shoot", g_assets.m_textures["projectile/blue.png"]);
        b->cprojectile = new CProjectile(1, 255);
        float dx = sf::Mouse::getPosition(g_window).x - player->csprite->getPosition().x;
        float dy = sf::Mouse::getPosition(g_window).y - player->csprite->getPosition().y;

        float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

        b->csprite->setPosition(player->csprite->getPosition().x, player->csprite->getPosition().y);
        b->ctransform = new CTransform(dx / l * 5, dy / l * 5);
        b->stationary = false;
    }
}

void Scenes_Play::sPhysics(std::vector<Entity *> &entities)
{

    // projectiles

    for (auto entity : entities)
    {
        if (entity->cprojectile != NULL)
        {
            if (entity->cprojectile->lifespan > 0)
            {
                entity->csprite->move(entity->ctransform->speedX, entity->ctransform->speedY);
                entity->cprojectile->lifespan--;
            }
            else
            {
                g_entities.removeEntity(entity->e_id);
            }
        }

        // collide
        for (int i = 0; i < entities.size(); i++)
        {
            if (entity->csprite->getGlobalBounds().intersects(entities[i]->csprite->getGlobalBounds()) && entity->e_id != entities[i]->e_id && (entity->tag != player->tag && entities[i]->tag != player->tag) && entity->layer == entities[i]->layer && entity->tag != entities[i]->tag)
            {
                entity->e_health--;
                entities[i]->e_health--;
                if(entity->cprojectile==NULL) {
                    entity->isHurt=true;
                }  else {
                    entities[i]->isHurt=true;
                }
            }
        }


        if(entity->e_health<=0) {
            g_entities.removeEntity(entity->e_id);
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

    sf::View view(sf::FloatRect(0.1f, 0.1f, 100.f, 60.f));
    view.rotate(5.f);
    view.setCenter(0, 0);
    view.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

    g_window.setView(view);

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
    g_assets.addTexture("slime/blue/4.png");


    g_assets.addTexture("projectile/blue.png");

    g_assets.addFont("noto.ttf");
}

void GameEngine::run()
{
    currentScene->init();
    while (is_running)
    {
        std::cout << frames / 60 << std::endl;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            g_window.create(fullscreenModes[0], "Bad FlappyBird");
        }

        while (g_window.pollEvent(events))
        {
            if (events.type == sf::Event::Closed)
            {
                g_window.close();
                is_running = false;
            }
        }

        currentScene->run();

        frames++;
    }
}

void changeScene(Scenes *scene)
{
    delete currentScene;
    currentScene = scene;
}