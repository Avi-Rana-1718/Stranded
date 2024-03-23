#include "../entities/_Entity.hpp"

#pragma once
class Scenes
{

public:
    Scenes();
    ~Scenes();

    float deltaTime;

    // functions
    virtual void run(float time);

    void sRender();
    void sEntityUpdate();
};

Scenes::Scenes()
{}

Scenes::~Scenes()
{
}

void Scenes::run(float time)
{
    // deltaTime = time;
    // sRender();
    // sEntityUpdate();
}

void Scenes::sRender()
{
    window.clear();

    // ui
    for (auto &entity : ui)
    {
        entity->sprite->setScale(sf::Vector2f(entity->direction * entity->scale, entity->scale));
        window.draw(*(entity->sprite));
        if (entity->text != NULL)
        {
            window.draw(*(entity->text));
        }
    }

    for (auto &entity : entities)
    {
        // std::cout<<entity->id<<" ";
        window.draw(*(entity->sprite));
        if (entity->text != NULL)
        {
            window.draw(*(entity->text));
        }

        entity->sprite->setScale(sf::Vector2f(entity->direction * entity->scale, entity->scale));

        sf::FloatRect bounds = entity->sprite->getGlobalBounds();
        sf::RectangleShape boundsRect(sf::Vector2f(bounds.width, bounds.height));
        boundsRect.setPosition(sf::Vector2f(bounds.getPosition().x, bounds.getPosition().y));
        boundsRect.setFillColor(sf::Color::Transparent);
        boundsRect.setOutlineColor(sf::Color::Red);
        boundsRect.setOutlineThickness(2.f);
        window.draw(boundsRect);
    }

    // std::cout<<std::endl;

    window.display();
}

void Scenes::sEntityUpdate()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->health <= 0)
        {
            delete entities[i];
            entities.erase(entities.begin() + i);
        }
    }
}