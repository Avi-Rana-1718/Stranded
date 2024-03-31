#include "_Entity.hpp"
#include "Explosion.hpp"
#pragma once
class BlueSkelWiz : public Entity
{

public:
    Entity *target = NULL;

    BlueSkelWiz();

    // functions
    void update(float time);

    void sMove();
    void sAttack();
};

BlueSkelWiz::BlueSkelWiz()
{
    hatesPlayer = true;
    target = entities[0];

    tag = "BlueSkelWiz";
    health = 10;

    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    lastActionFrame = gameTime.getElapsedTime().asSeconds();

    //
    animationMap["idle"].push_back(m_textures["blueSkeletonWizard/idle0.png"]);
    animationMap["move"].push_back(m_textures["blueSkeletonWizard/idle1.png"]);
    animationMap["move"].push_back(m_textures["blueSkeletonWizard/idle2.png"]);
    animationMap["move"].push_back(m_textures["blueSkeletonWizard/idle3.png"]);
    animationMap["attack"].push_back(m_textures["blueSkeletonWizard/attack0.png"]);
    animationMap["attack"].push_back(m_textures["blueSkeletonWizard/attack1.png"]);
    animationMap["attack"].push_back(m_textures["blueSkeletonWizard/attack2.png"]);
    animationMap["attack"].push_back(m_textures["blueSkeletonWizard/attack3.png"]);
    animationMap["attack"].push_back(m_textures["blueSkeletonWizard/attack4.png"]);
    animationMap["attack"].push_back(m_textures["blueSkeletonWizard/attack5.png"]);
    animationMap["hurt"].push_back(m_textures["blueSkeletonWizard/hit.png"]);
    animationMap["die"].push_back(m_textures["blueSkeletonWizard/die.png"]);

    sprite = new CSprite(m_textures["blueSkeletonWizard/idle0.png"]);
    sprite->setOrigin(m_textures["blueSkeletonWizard/idle0.png"].getSize().x / 2, m_textures["blueSkeletonWizard/idle0.png"].getSize().y / 2);
    sprite->setPosition(sf::Vector2f((rand() % 1000 - 100) + 100, (rand() % 500 - 100) + 100));
    transform = new CTransform(150, 150);

    scale = 3.5;
    actionTag="idle";
}

void BlueSkelWiz::update(float time)
{
    deltaTime = time;
    sMove();
    sAttack();
    sAnimate();

    // if (health <= 0)
    // {
    //     actionTag="die";
    //     for (int i = 0; i < entities.size(); i++)
    //     {
    //         if (this->id == entities[i]->id)
    //         {
    //             entities.erase(entities.begin() + i);
    //             break;
    //         }
    //     }
    //     delete this;
    // }
}

void BlueSkelWiz::sMove()
{
    actionTag="move";
    float dx = target->sprite->getPosition().x - sprite->getPosition().x;
    float dy = target->sprite->getPosition().y - sprite->getPosition().y;

    if (dx > 0)
    {
        direction = 1;
    }
    else
    {
        direction = -1;
    }

    float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);
    sprite->move((dx / l) * deltaTime * transform->speedX, (dy / l) * deltaTime * transform->speedY);
}

void BlueSkelWiz::sAttack()
{
    // range of sight/detection
    sf::FloatRect bounds = this->sprite->getGlobalBounds();
    sf::RectangleShape rec(sf::Vector2f(bounds.getSize().x + 600, bounds.getSize().y + 600));
    rec.setOrigin(sf::Vector2f(rec.getSize().x / 2, rec.getSize().y / 2));
    rec.setPosition(this->sprite->getPosition().x, this->sprite->getPosition().y);

    if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 1 && rec.getGlobalBounds().intersects(target->sprite->getGlobalBounds()))
    {
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
        Entity *projectile = new Explosion(sprite->getPosition().x, sprite->getPosition().y, target->sprite->getPosition().x, target->sprite->getPosition().y, id);
        entities.push_back(projectile);
        actionTag="attack";
    }
}