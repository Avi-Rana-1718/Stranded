#include "_Entity.hpp"
#include "spells/_Spells.hpp"
#pragma once
class Archer : public Entity
{

public:
    Entity *target = NULL;
    bool inRange;

    Archer();

    // functions
    void update(float time);

    void sMove();
    void sAttack();
};

Archer::Archer()
{
    hatesPlayer = true;
    target = entities[0];
    inRange = false;

    tag = "Archer";
    health = 4;

    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    lastActionFrame = gameTime.getElapsedTime().asSeconds();

    //
    animationMap["idle"].push_back(m_textures["archer/idle0.png"]);
    animationMap["idle"].push_back(m_textures["archer/idle1.png"]);
    animationMap["idle"].push_back(m_textures["archer/idle2.png"]);
    animationMap["idle"].push_back(m_textures["archer/idle3.png"]);
    animationMap["idle"].push_back(m_textures["archer/idle4.png"]);

    animationMap["move"].push_back(m_textures["archer/move0.png"]);
    animationMap["move"].push_back(m_textures["archer/move1.png"]);
    animationMap["move"].push_back(m_textures["archer/move2.png"]);
    animationMap["move"].push_back(m_textures["archer/move3.png"]);

    animationMap["attack"].push_back(m_textures["archer/attack0.png"]);
    animationMap["attack"].push_back(m_textures["archer/attack1.png"]);
    animationMap["attack"].push_back(m_textures["archer/attack2.png"]);
    animationMap["attack"].push_back(m_textures["archer/attack3.png"]);
    animationMap["attack"].push_back(m_textures["archer/attack4.png"]);
    animationMap["attack"].push_back(m_textures["archer/attack5.png"]);
    animationMap["attack"].push_back(m_textures["archer/attack6.png"]);

    animationMap["hurt"].push_back(m_textures["archer/hurt.png"]);
    animationMap["die"].push_back(m_textures["archer/die.png"]);

    sprite = new CSprite(m_textures["archer/idle0.png"]);
    sprite->setOrigin(m_textures["archer/idle0.png"].getSize().x / 2, m_textures["archer/idle0.png"].getSize().y / 2);
    sprite->setPosition(sf::Vector2f((rand() % WINDOW_W - 100) + 100, (rand() % WINDOW_H - 100) + 100));
    transform = new CTransform(130, 130);

    scale = 4;
    actionTag = "idle";
}

void Archer::update(float time)
{
    if (actionTag != "die")
    {
        deltaTime = time;
        sAnimate();
        sAttack();
        sMove();
    }
}

void Archer::sMove()
{
    if (inRange == false)
    {
        if (actionTag != "die" && actionTag != "hurt" && actionTag != "attack")
        {
            actionTag = "move";
        }

        float dx = target->sprite->getPosition().x - sprite->getPosition().x;
        float dy = target->sprite->getPosition().y - sprite->getPosition().y;

        float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);
        sprite->move((dx / l) * deltaTime * transform->speedX, (dy / l) * deltaTime * transform->speedY);
    }

    if (target->sprite->getPosition().x - sprite->getPosition().x > 0)
    {
        rotate = 1;
    }
    else
    {
        rotate = -1;
    }
}

void Archer::sAttack()
{
    // range of sight/detection
    sf::FloatRect bounds = this->sprite->getGlobalBounds();
    sf::RectangleShape rec(sf::Vector2f(bounds.getSize().x + 600, bounds.getSize().y + 600));
    rec.setOrigin(sf::Vector2f(rec.getSize().x / 2, rec.getSize().y / 2));
    rec.setPosition(this->sprite->getPosition().x, this->sprite->getPosition().y);

    if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 1 && rec.getGlobalBounds().intersects(target->sprite->getGlobalBounds()))
    {
        if (currentFrame == animationMap["attack"].size() - 1)
        {
            lastActionFrame = gameTime.getElapsedTime().asSeconds();
            Entity *projectile = new Spells(sprite->getPosition().x, sprite->getPosition().y, target->sprite->getPosition().x, target->sprite->getPosition().y, id);
            // projectile->particles->color = sf::Color(32, 178, 170);
            entities.push_back(projectile);
        }
        inRange = true;

        if (actionTag != "hurt" && actionTag != "die")
        {
            actionTag = "attack";
        }
    }
    else if (!rec.getGlobalBounds().intersects(target->sprite->getGlobalBounds()))
    {
        inRange = false;
        currentFrame = 0;
        // actionTag="idle";
    }
}