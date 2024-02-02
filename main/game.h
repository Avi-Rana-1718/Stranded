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

    std::vector<sf::CircleShape> bounds;

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
    void displayDevConsole(const std::vector<Entity *> &entities);

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

        SUserInterface();
        spawnEnemy();

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
                displayDevConsole(entities.getEntities());
            }

            frames++;
        }
    };
};

// Systems

void Game::SDraw(const std::vector<Entity *> &entities)
{
    window.clear();

    // Draw Bounds
    for (auto entity : bounds)
    {
        window.draw(entity);
    }

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
        if ((entity->ctransform != NULL) && (entity->controllable == false))
        {
            entity->cshape->circle.setPosition(entity->ctransform->posX += entity->ctransform->speedX, entity->ctransform->posY += entity->ctransform->speedY);
        }
        else if (entity->ctransform != NULL)
        {
            entity->cshape->circle.setPosition(entity->ctransform->posX, entity->ctransform->posY);
        }
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
            if ((entity->ctransform->posX < 0) || (entity->ctransform->posX  + entity->cshape->radius*2 > WINDOW_WIDTH))
            {
                entity->ctransform->speedX *= -1;
            }
            if ((entity->ctransform->posY < 0) || (entity->ctransform->posY + entity->cshape->radius*2 > WINDOW_HEIGHT))
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
    return entities.addEntities("Player", 50.f, 6.f, 100.f, 110.f, 10.f, 10.f, sf::Color(220, 20, 60), sf::Color(255, 255, 255), 1, true);
}

void Game::displayDevConsole(const std::vector<Entity *> &entities)
{
    labels[0].setString(std::to_string(frames / 60) + "\nTotal enities: " + std::to_string(entities.size()));

    bounds.erase(bounds.begin(), bounds.end());

    // for (auto entity : entities)
    // {
    //     sf::CircleShape temp(entity->cshape->radius, 4.f);
    //     temp.setPosition(entity->ctransform->posX, entity->ctransform->posY);
    //     temp.setFillColor(sf::Color(0, 0, 0, 0));
    //     temp.setOutlineThickness(1);
    //     temp.setOutlineColor(sf::Color::White);
    //     bounds.push_back(temp);
    // }
}

void Game::spawnEnemy()
{

    for (int i = 0; i < 5000; i++)
    {
        entities.addEntities("Enemy", 40.f, 4.f, 500.f + i * 60, 300.f + i * 60, 1.f, 2.f, sf::Color(0, 255, 128), sf::Color(255, 255, 255), 1);
        entities.addEntities("Enemy", 45.f, 4.f, 100.f + i * 60, 200.f + i * 60, 2.f, 2.f, sf::Color(255, 102, 178), sf::Color(255, 255, 255), 1);
        entities.addEntities("Enemy", 30.f, 4.f, 300.f + i * 60, 100.f + i * 60, 5.f, 3.f, sf::Color(102, 178, 255), sf::Color(255, 255, 255), 1);
    }
}