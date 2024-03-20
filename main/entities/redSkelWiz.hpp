#include "_Entity.hpp"
#include "Explosion.hpp"
#pragma once
class RedSkelWiz : public Entity
{

public:
    Entity *target = NULL;

    RedSkelWiz();

    // functions
    void update(float time);

    void sMove();
    void sAttack();
};

RedSkelWiz::RedSkelWiz()
{
    hatesPlayer = true;
    target=entities[0];

    tag = "RedSkelWiz";
    health = 10;

    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    lastActionFrame = 0;

    //
    animationMap["idle"].push_back(m_textures["redSkeletonWizard/idle0.png"]);
    animationMap["move"].push_back(m_textures["redSkeletonWizard/idle1.png"]);
    animationMap["move"].push_back(m_textures["redSkeletonWizard/idle2.png"]);
    animationMap["move"].push_back(m_textures["redSkeletonWizard/idle3.png"]);
    animationMap["attack"].push_back(m_textures["redSkeletonWizard/attack0.png"]);
    animationMap["attack"].push_back(m_textures["redSkeletonWizard/attack1.png"]);
    animationMap["attack"].push_back(m_textures["redSkeletonWizard/attack2.png"]);
    animationMap["attack"].push_back(m_textures["redSkeletonWizard/attack3.png"]);
    animationMap["attack"].push_back(m_textures["redSkeletonWizard/attack4.png"]);
    animationMap["attack"].push_back(m_textures["redSkeletonWizard/attack5.png"]);
    animationMap["hurt"].push_back(m_textures["redSkeletonWizard/hit.png"]);
    animationMap["die"].push_back(m_textures["redSkeletonWizard/die.png"]);

    sprite = new CSprite(m_textures["redSkeletonWizard/idle0.png"]);
    sprite->setOrigin(m_textures["redSkeletonWizard/idle0.png"].getSize().x / 2, m_textures["redSkeletonWizard/idle0.png"].getSize().y / 2);
    sprite->setPosition(sf::Vector2f((rand() % 1000 - 100) + 100, (rand() % 500 - 100) + 100));
    transform = new CTransform(100, 100);

    scale = 3.5;
    isMoving = false;
}

void RedSkelWiz::update(float time)
{
    deltaTime = time;
    sMove();
    sAttack();
    sAnimate();
}

void RedSkelWiz::sMove()
{
    isMoving = true;
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

void RedSkelWiz::sAttack()
{
    // sf::RectangleShape bounds = this->sprite->getGlobalBounds();
    // bounds.setSize(sf::Vector2f(bounds.getSize().x+100, bounds.getSize().y+100));


    if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 1)
    {
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
        Entity *projectile = new Explosion(sprite->getPosition().x, sprite->getPosition().y, target->sprite->getPosition().x, target->sprite->getPosition().y, id);
        entities.push_back(projectile);
        isAttacking = true;
    }
}