#include "../entities/_Entity.hpp"
#include "../particles.hpp"

#pragma once
class Scenes
{

public:

    ~Scenes();

    float deltaTime;

    // functions
    virtual void init();
    virtual void run(float time);

    void sRender();
    void sEntityUpdate();
};

void Scenes::init() {
        ui.erase(ui.begin(), ui.end());
        entities.erase(entities.begin(), entities.end());
        background.erase(background.begin(), background.end());
}

Scenes::~Scenes()
{
    if (!ui.empty())
    {
        ui.erase(ui.begin(), ui.end());
    }

    if (!entities.empty())
    {
        entities.erase(entities.begin(), entities.end());
    }
}

void Scenes::run(float time)
{
    // deltaTime = time;
    // sRender();
    // sEntityUpdate();
}

void Scenes::sRender()
{
    window.clear(sf::Color(81, 58, 61));

    // background
    for (auto &entity : background)
    {
        if (entity->sprite != NULL)
        {
            entity->sprite->setScale(sf::Vector2f(entity->rotate * entity->scale, entity->scale));
            window.draw(*(entity->sprite));
        }
        if (entity->text != NULL)
        {
            window.draw(*(entity->text));
        }
    }

    // entities
    for (auto &entity : entities)
    {
        if (entity->sprite != NULL)
        {
            window.draw(*(entity->sprite));
            entity->sprite->setScale(sf::Vector2f(entity->rotate * entity->scale, entity->scale));
        }
        if (entity->text != NULL)
        {
            window.draw(*(entity->text));
        }

        // sf::FloatRect bounds = entity->sprite->getGlobalBounds();
        // sf::RectangleShape boundsRect(sf::Vector2f(bounds.width, bounds.height));
        // boundsRect.setPosition(sf::Vector2f(bounds.getPosition().x, bounds.getPosition().y));
        // boundsRect.setFillColor(sf::Color::Transparent);
        // boundsRect.setOutlineColor(sf::Color::Red);
        // boundsRect.setOutlineThickness(2.f);
        // window.draw(boundsRect);
    }

    // ui
    for (auto &entity : ui)
    {
        if (entity->sprite != NULL)
        {
            entity->sprite->setScale(sf::Vector2f(entity->rotate * entity->scale, entity->scale));
            window.draw(*(entity->sprite));
        }
        if (entity->text != NULL)
        {
            window.draw(*(entity->text));
        }
        if(entity->particles!=NULL) {
            window.draw(entity->particles->vertices);
        }
        if(entity->shape!=NULL) {
            window.draw(*entity->shape);
        }
    }

    window.display();
}

void Scenes::sEntityUpdate()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->actionTag == "die" && gameTime.getElapsedTime().asSeconds() > entities[i]->animationTimer + entities[i]->frameDelay)
        {
            delete entities[i];
            entities.erase(entities.begin() + i);
        }
    }
}