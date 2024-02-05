#include "entityManager.h"
#include <math.h>
#include <string>

// Constants

#define WINDOW_WIDTH sf::VideoMode::getDesktopMode().width
#define WINDOW_HEIGHT 720

sf::Font font;

class Game
{
    sf::RenderWindow g_window;
    sf::Event event;

    EntityManager g_entities;
    std::vector<sf::Text> labels;

    bool is_running = true;
    int frames;

    bool devMode = false;

    // System declarations

    void SDraw(const std::vector<Entity *> &entities);
    void SMove(const std::vector<Entity *> &entities);
    void SInput(Entity *player); // player input
    void SCollision(const std::vector<Entity *> &entities);

    void SUserInterface();

    // Helper functions declarations

    Entity *spawnPlayer();
    void spawnEnemy();
    void spawnBullet();


    void displayDevConsole(const std::vector<Entity *> &entities);

    // Textures declaration
    CTexture playerTexture;
    CTexture skeletonTexture;
    CTexture vampireTexture;

    CTexture arrowTexture;

public:
    Entity *player;
    Game()
    {
        g_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
        g_window.setFramerateLimit(60);

        // load textures
        playerTexture.set("player_idle.png");
        skeletonTexture.set("skeleton_idle.png");
        vampireTexture.set("vampire_idle.png");
        arrowTexture.set("arrow.png");

        player = spawnPlayer();

        frames = 0;
        is_running = true;

        // fonts
        if (!font.loadFromFile("assets/noto.ttf"))
        {
            std::cout << "Font not found!";
        }
    }

    void run()
    {

        SUserInterface();
        spawnEnemy();

        while (is_running)
        {
            while (g_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    is_running = false;
                    g_window.close();
                }
            }

            SDraw(g_entities.getEntities());
            SMove(g_entities.getEntities());
            SCollision(g_entities.getEntities());
            SInput(player);

            if (devMode)
            {
                displayDevConsole(g_entities.getEntities());
            }

            frames++;
        }
    };
};

// Systems

void Game::SDraw(const std::vector<Entity *> &entities)
{
    g_window.clear();

    for (auto &entity : entities)
    {
        if (entity->csprite != NULL)
        {
            g_window.draw(entity->csprite->sprite);
        }
    }

    // Draw UI
    for (auto &text : labels)
    {
        g_window.draw(text);
    }

    g_window.display();
}

void Game::SMove(const std::vector<Entity *> &entities)
{

    for (auto &entity : entities)
    {
        if ((entity->ctransform != NULL) && (entity->controllable == false))
        {
            entity->csprite->sprite.setPosition(entity->ctransform->posX += entity->ctransform->speedX, entity->ctransform->posY += entity->ctransform->speedY);
        }
        else if (entity->ctransform != NULL)
        {
            entity->csprite->sprite.setPosition(entity->ctransform->posX, entity->ctransform->posY);
        }
    }
}

void Game::SInput(Entity *player)
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (player->ctransform->posX > 0))
    {
        player->ctransform->posX -= player->ctransform->speedX;
        player->csprite->sprite.setScale(sf::Vector2f(-1*player->scale, player->scale));
        player->csprite->sprite.setOrigin(player->w/player->scale, 0);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (player->ctransform->posX + player->w < WINDOW_WIDTH))
    {
        player->ctransform->posX += player->ctransform->speedX;
        player->csprite->sprite.setScale(sf::Vector2f(player->scale, player->scale));
        player->csprite->sprite.setOrigin(0, 0);
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (player->ctransform->posY > 0))
    {
        player->ctransform->posY -= player->ctransform->speedY;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (player->ctransform->posY + player->h < WINDOW_HEIGHT))
    {
        player->ctransform->posY += player->ctransform->speedY;
    }

    //

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
    {
        devMode = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        spawnBullet();
    }
}

void Game::SCollision(const std::vector<Entity *> &entities)
{

    for (int i = 0; i < entities.size(); i++)
    {

        if ((entities[i]->ctransform != NULL) && (entities[i]->controllable != true))
        {
            if ((entities[i]->ctransform->posX < 0) || (entities[i]->ctransform->posX + entities[i]->h > WINDOW_WIDTH))
            {
                entities[i]->ctransform->speedX *= -1;
            }
            if ((entities[i]->ctransform->posY < 0) || (entities[i]->ctransform->posY + entities[i]->w > WINDOW_HEIGHT))
            {
                entities[i]->ctransform->speedY *= -1;
            }
        }

        for (int j = i + 1; j < entities.size(); j++)
        {
            if (entities[i]->csprite->sprite.getGlobalBounds().intersects(entities[j]->csprite->sprite.getGlobalBounds()) && entities[i]->e_id != entities[j]->e_id)
            {
                if (entities[i]->tag != "Player")
                {
                    entities[i]->ctransform->speedX *= -1;
                    entities[i]->ctransform->speedY *= -1;
                }
                else
                {
                    g_entities.removeEntity(entities[j]->e_id);
                }

                if (entities[j]->tag != "Player")
                {
                    entities[j]->ctransform->speedX *= -1;
                    entities[j]->ctransform->speedY *= -1;
                }
                else
                {
                    g_entities.removeEntity(entities[i]->e_id);
                }
            }

            if (entities[i]->tag == entities[j]->tag && entities[i]->ctransform->posX == entities[j]->ctransform->posX && entities[i]->ctransform->posY == entities[j]->ctransform->posY)
            {
                g_entities.removeEntity(entities[i]->e_id);
            }
        }
    }
}

void Game::SUserInterface()
{

    sf::Text text;

    // select the font
    text.setFont(font); // font is a sf::Font
    text.setString("Hello world!");
    text.setCharacterSize(24); // in pixels, not points!

    labels.push_back(text);

    sf::Text text2;

    // select the font
    text2.setFont(font); // font is a sf::Font
    text2.setString("100");
    text2.setCharacterSize(24); // in pixels, not points!
    text2.setPosition(0, WINDOW_HEIGHT - 24);
    labels.push_back(text2);
}

// Helper functions

Entity *Game::spawnPlayer()
{
    return g_entities.addEntities("Player", 10.f, 10.f, playerTexture.texture, true);
}

void Game::displayDevConsole(const std::vector<Entity *> &entities)
{
    labels[0].setString(std::to_string(frames / 60) + "\nTotal enities: " + std::to_string(entities.size()));
}

void Game::spawnEnemy()
{

    for (int i = 0; i < 4; i++)
    {
        g_entities.addEntities("Skeleton", 1, 1, skeletonTexture.texture);
        g_entities.addEntities("Skeleton", 1, 1, skeletonTexture.texture);
        g_entities.addEntities("Vampire", 1, 1, vampireTexture.texture);
    }
}

void Game::spawnBullet()
{
    g_entities.addEntities("Arrow", 1, 1, arrowTexture.texture);
}