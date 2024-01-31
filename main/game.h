#include "entityManager.h"
#include <math.h>
// Constants

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 720

sf::Font font;

class Game
{
    sf::RenderWindow window;
    EntityManager entities;
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
    void displayDevConsole();

public:
    Entity *player;
    Game()
    {
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
        window.setFramerateLimit(60);

        player = spawnPlayer();

        frames = 0;

        // fonts
        if (!font.loadFromFile("assets/noto.ttf"))
        {
            std::cout << "Font not found!";
        }
    }

    void run()
    {
        // declarations
        entities.addEntities("Enemy", 40, 3, 400, 100, 1, 2, sf::Color(0, 255, 128));
        entities.addEntities("Enemy", 45, 5, 300, 200, 2, 2, sf::Color(255, 102, 178));
        entities.addEntities("Enemy", 30, 4, 600, 400, 5, 3, sf::Color(102, 178, 255));
        entities.addEntities("Enemy", 40, 3, 400, 100, 3, 2, sf::Color(0, 255, 128));
        entities.addEntities("Enemy", 45, 5, 300, 200, 5, 2, sf::Color(255, 102, 178));
        entities.addEntities("Enemy", 30, 4, 600, 400, 1, 3, sf::Color(102, 178, 255));

        SUserInterface();

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
            SCollision(entities.getEntities());
            SInput(player);

            if (devMode)
            {
                displayDevConsole();
            }

            frames++;
        }
    };
};

// Systems

void Game::SDraw(const std::vector<Entity *> &entities)
{
    window.clear();
    for (auto entity : entities)
    {
        if (entity->cshape != NULL)
        {
            entity->cshape->circle.rotate(1.f);
            window.draw(entity->cshape->circle);
        }
    }

    // Draw UI
    for (auto text : labels)
    {
        window.draw(text);
    }

    window.display();
}

void Game::SMove(const std::vector<Entity *> &entities)
{

    for (auto entity : entities)
    {
        if ((entity->ctransform != NULL) && (entity->controllable == false))
        {
            entity->cshape->circle.setPosition(entity->ctransform->posX += entity->ctransform->speedX, entity->ctransform->posY += entity->ctransform->speedY);
        }
        else if (entity->ctransform != NULL)
        {
            entity->cshape->circle.setPosition(entity->ctransform->posX, entity->ctransform->posY);
        }

    //     for (auto entity2 : entities)
    //     {

    // sf::Vector2f bound = 

    //     }
    }
}

void Game::SInput(Entity *player)
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (player->ctransform->posX - player->cshape->radius > 0))
    {
        player->ctransform->posX -= player->ctransform->speedX;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (player->ctransform->posX + player->cshape->radius < WINDOW_WIDTH))
    {
        player->ctransform->posX += player->ctransform->speedX;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (player->ctransform->posY - player->cshape->radius > 0))
    {
        player->ctransform->posY -= player->ctransform->speedY;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (player->ctransform->posY + player->cshape->radius < WINDOW_HEIGHT))
    {
        player->ctransform->posY += player->ctransform->speedY;
    }

    //

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
    {
        devMode = true;
    }
}

void Game::SCollision(const std::vector<Entity *> &entities)
{
    for (auto entity : entities)
    {
        if ((entity->ctransform != NULL) && (entity->controllable != true))
        {
            if ((entity->ctransform->posX - entity->cshape->radius < 0) || (entity->ctransform->posX + entity->cshape->radius > WINDOW_WIDTH))
            {
                entity->ctransform->speedX *= -1;
            }
            if ((entity->ctransform->posY - entity->cshape->radius < 0) || (entity->ctransform->posY + entity->cshape->radius > WINDOW_HEIGHT))
            {
                entity->ctransform->speedY *= -1;
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
}

// Helper functions

Entity *Game::spawnPlayer()
{
    return entities.addEntities("Player", 50, 6, 100, 110, 10, 10, sf::Color(220, 20, 60), sf::Color(255, 255, 255), 1, true);
}

void Game::displayDevConsole()
{
    labels[0].setString("Dev console \nFPS Limit: 60\nTime elapsed: " + std::to_string(frames / 60));
}