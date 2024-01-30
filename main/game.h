#include "entityManager.h"

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

    // System declarations

    void SDraw(const std::vector<Entity *> &entities);
    void SMove(const std::vector<Entity *> &entities);
    void SInput(Entity *player); // player input
    void SUserInterface();

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
        entities.addEntities("Enemy", 10, 3, 0, 0, 1, 2);

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
            SInput(player);

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
        if ((entity->ctransfrom != NULL) && (entity->controllable == false))
        {
            entity->cshape->circle.setPosition(entity->ctransfrom->posX += entity->ctransfrom->speedX, entity->ctransfrom->posY += entity->ctransfrom->speedY);
        }
        else if (entity->ctransfrom != NULL)
        {
            entity->cshape->circle.setPosition(entity->ctransfrom->posX, entity->ctransfrom->posY);
        }
    }
}

void Game::SInput(Entity *player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->ctransfrom->posX -= player->ctransfrom->speedX;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->ctransfrom->posX += player->ctransfrom->speedX;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player->ctransfrom->posY -= player->ctransfrom->speedY;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player->ctransfrom->posY += player->ctransfrom->speedY;
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
    return entities.addEntities("Player", 50, 6, 100, 110, 10, 10, true);
}
