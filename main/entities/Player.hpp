#include "_Entity.hpp"
#include "spells/_Spells.hpp"
#pragma once
class Player : public Entity
{

public:
    Player();


    // int dashActionFrame;

    // functions
    void update(float time);

    void sInput();
};

Player::Player()
{

    tag = "Player";
    health = 10;

    // projectile props
    playerProps.projectileDamage = 1;
    playerProps.projectileHealth = 1;
    playerProps.projectileLifetime = 3;
    playerProps.projectileFirerate = 1;

    frameDelay = 0.2;
    animationTimer = 0;
    currentFrame = 0;
    lastActionFrame = 0;
    // dashActionFrame = 0;

    //
    animationMap["idle"].push_back(m_textures["player/idle0.png"]);
    animationMap["idle"].push_back(m_textures["player/idle1.png"]);
    animationMap["idle"].push_back(m_textures["player/idle2.png"]);
    animationMap["idle"].push_back(m_textures["player/idle3.png"]);
    animationMap["idle"].push_back(m_textures["player/idle4.png"]);

    animationMap["move-horizontal"].push_back(m_textures["player/move-h0.png"]);
    animationMap["move-horizontal"].push_back(m_textures["player/move-h1.png"]);
    animationMap["move-horizontal"].push_back(m_textures["player/move-h2.png"]);
    animationMap["move-horizontal"].push_back(m_textures["player/move-h3.png"]);

    animationMap["hurt"].push_back(m_textures["player/hurt.png"]);

    animationMap["die"].push_back(m_textures["player/die.png"]);

    sprite = new CSprite(m_textures["player/idle0.png"]);
    sprite->setOrigin(m_textures["player/idle0.png"].getSize().x / 2, m_textures["spells/explosion/0.png"].getSize().y / 2);
    sprite->setPosition(sf::Vector2f(300, 300));

    scale = 4;

    transform = new CTransform(320.f, 320.f);
    actionTag = "idle";
}

void Player::update(float time)
{
    deltaTime = time;
    if (actionTag != "die")
    {
        sInput();
        sAnimate();
    }
}

void Player::sInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite->getPosition().y > 0 + m_textures["spells/explosion/0.png"].getSize().y / 2)
    {
        sprite->move(0, -transform->speedY * deltaTime);
        actionTag = (actionTag != "attack") ? "move" : "attack";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite->getPosition().y < WINDOW_H - m_textures["spells/explosion/0.png"].getSize().y / 2)
    {
        sprite->move(0, transform->speedY * deltaTime);
        actionTag = (actionTag != "attack") ? "move" : "attack";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite->getPosition().x > 0 + m_textures["spells/explosion/0.png"].getSize().x / 2)
    {
        sprite->move(-transform->speedX * deltaTime, 0);
        actionTag = (actionTag != "attack") ? "move" : "attack";
        direction = "right";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite->getPosition().x < WINDOW_W - m_textures["spells/explosion/0.png"].getSize().x / 2)
    {
        sprite->move(transform->speedX * deltaTime, 0);
        actionTag = (actionTag != "attack") ? "move" : "attack";
        direction = "left";
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Event::MouseButtonReleased && gameTime.getElapsedTime().asSeconds() > lastActionFrame + playerProps.projectileFirerate)
    {
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
        Entity *projectile = new Spells(sprite->getPosition().x, sprite->getPosition().y, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, id, playerProps.projectileDamage, playerProps.projectileHealth, playerProps.projectileLifetime);
        entities.push_back(projectile);
    }

    // dash

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameTime.getElapsedTime().asSeconds() > dashActionFrame - 5)
    // {

    //     dashActionFrame = gameTime.getElapsedTime().asSeconds() + 10;
    //     isInvulnerable=true;

    //     float dx = sf::Mouse::getPosition(window).x - sprite->getPosition().x;
    //     float dy = sf::Mouse::getPosition(window).y - sprite->getPosition().y;

    //     float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

    //     sprite->move(dx / l * 12000 * deltaTime, dy / l * 12000 * deltaTime);
    // } else if (isInvulnerable && gameTime.getElapsedTime().asSeconds() > dashActionFrame + 1) {
    //     isInvulnerable=false;
    // }
}
