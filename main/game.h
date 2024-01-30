#include "entityManager.h"
#include "vector2.h"

// Constants

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 720

class Game
{
    sf::RenderWindow window;
    EntityManager entities;

    bool is_running = true;

    // System declarations

    void SDraw(const std::vector<Entity *> &entities);
    void SMove(const std::vector<Entity *> &entities);
    void SInput(Entity *player); // player input

    // Helper functions declarations

    Entity *spawnPlayer();

    // todo
    void SCollision(); // collision system

public:
    Entity *player;
    Game()
    {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
        window.setFramerateLimit(60);
        player = spawnPlayer();
    }

    void run()
    {
        // declarations
        entities.addEntities("Enemy", 0, 0, 1, 2);

        while (is_running)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    is_running = false;
                    window.close();
                }
            }

            SDraw(entities.getEntities());
            SMove(entities.getEntities());
            SInput(player);
        }
    };
};

// Systems

void Game::SDraw(const std::vector<Entity *> &entities)
{
    window.clear();
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->cshape != NULL)
        {
            window.draw(entities[i]->cshape->circle);
        }
    }
    window.display();
}

void Game::SMove(const std::vector<Entity *> &entities)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if ((entities[i]->ctransfrom != NULL) && (entities[i]->cinput == NULL))
        {
            entities[i]->cshape->circle.setPosition(entities[i]->ctransfrom->posX += entities[i]->ctransfrom->speedX, entities[i]->ctransfrom->posY += entities[i]->ctransfrom->speedY);
        }
    }
}

void Game::SInput(Entity *player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->cshape->circle.setPosition(player->ctransfrom->posX -= player->ctransfrom->speedX, player->ctransfrom->posY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->cshape->circle.setPosition(player->ctransfrom->posX += player->ctransfrom->speedX, player->ctransfrom->posY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player->cshape->circle.setPosition(player->ctransfrom->posX, player->ctransfrom->posY -= player->ctransfrom->speedY);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player->cshape->circle.setPosition(player->ctransfrom->posX, player->ctransfrom->posY += player->ctransfrom->speedY);
    }
}

// Helper functions

Entity *Game::spawnPlayer()
{
    return entities.addEntities("Player", 100, 110, 10, 10, true);
}