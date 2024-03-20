#include "_Entity.hpp"
#include "Explosion.hpp"
#pragma once
class Player : public Entity
{

public:
    Player();

    // functions
    void update(float time);

    void sInput();
};

Player::Player()
{

    tag = "Player";
    health = 1000;

    lastActionFrame = -1;
    frameDelay = 0.2;
    animationTimer = 0;
    currentFrame = 0;

    //
    animationMap["idle"].push_back(m_textures["blueWizard/idle0.png"]);
    animationMap["idle"].push_back(m_textures["blueWizard/idle1.png"]);
    animationMap["idle"].push_back(m_textures["blueWizard/idle2.png"]);
    animationMap["idle"].push_back(m_textures["blueWizard/idle3.png"]);
    animationMap["move"].push_back(m_textures["blueWizard/idle0.png"]);
    animationMap["move"].push_back(m_textures["blueWizard/idle1.png"]);
    animationMap["move"].push_back(m_textures["blueWizard/idle2.png"]);
    animationMap["move"].push_back(m_textures["blueWizard/idle3.png"]);
    animationMap["attack"].push_back(m_textures["blueWizard/attack0.png"]);
    animationMap["attack"].push_back(m_textures["blueWizard/attack1.png"]);
    animationMap["attack"].push_back(m_textures["blueWizard/attack2.png"]);
    animationMap["attack"].push_back(m_textures["blueWizard/attack3.png"]);
    animationMap["hurt"].push_back(m_textures["blueWizard/hurt0.png"]);
    animationMap["die"].push_back(m_textures["blueWizard/die.png"]);

    sprite = new CSprite(m_textures["blueWizard/idle0.png"]);
    sprite->setOrigin(m_textures["blueWizard/idle0.png"].getSize().x / 2, m_textures["spells/explosion/0.png"].getSize().y / 2);
    sprite->setPosition(sf::Vector2f(100, 100));

    scale = 4;

    transform = new CTransform(500.f, 500.f);
}

void Player::update(float time)
{
    deltaTime = time;
    sInput();
    sAnimate();
}

void Player::sInput()
{
    isMoving = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sprite->move(0, -transform->speedY * deltaTime);
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        sprite->move(0, transform->speedY * deltaTime);
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sprite->move(-transform->speedX * deltaTime, 0);
        isMoving = true;
        direction = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite->move(transform->speedX * deltaTime, 0);
        isMoving = true;
        direction = 1;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Event::MouseButtonReleased && gameTime.getElapsedTime().asSeconds() > lastActionFrame + 1)
    {
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
        Entity *projectile = new Explosion(sprite->getPosition().x, sprite->getPosition().y, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, id);
        entities.push_back(projectile);
        isAttacking = true;
    }
}
