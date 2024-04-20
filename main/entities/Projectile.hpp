#include "_Entity.hpp"
#pragma once

class Shell : public Entity, public Projectile
{
public:
    Entity *lastTarget;

    Shell(float originX, float originY, float targetX, float targetY, int id, float damage, int phealth, int life);
    std::vector<sf::Color> colors;

    void update(float time);
    // void sAnimate();
    void sMove();

    void Collide();
};

Shell::Shell(float originX, float originY, float targetX, float targetY, int id, float damage = 1, int phealth = 1, int life = 2)
{
    hatesPlayer = false;
    isProjectile = true;
    tag = "Explosion";

    ownerID = id;
    dmg = damage;
    projectileHealth = phealth;
    lifetime = life; // in sec

    lastActionFrame = 0;
    lastTarget = NULL;

    sprite = new CSprite(m_textures["shell/explosion/0.png"]);
    sprite->setOrigin(m_textures["shell/explosion/0.png"].getSize().x / 2, m_textures["shell/explosion/0.png"].getSize().y / 2);
    sprite->setPosition(sf::Vector2f(originX, originY));

    // particles = new ParticleSystem(targetX, targetY);

    float dx = targetX - originX;
    float dy = targetY - originY;

    float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

    transform = new CTransform(dx / l * 500, dy / l * 500);

    scale = 1;

    colors.push_back(sf::Color(132,224,107));
    colors.push_back(sf::Color(255,255,255));
    colors.push_back(sf::Color(107,210,224));
    colors.push_back(sf::Color(229,116,0));

    sprite->setColor(colors[std::rand()%4]);
  

    sound.setBuffer(m_sounds["shot.wav"]);
    sound.setPitch(gameSpeed);
    sound.play();
}

void Shell::update(float time)
{

    deltaTime = time;
    sMove();

    if (gameTime.getElapsedTime().asSeconds()*gameSpeed > lastActionFrame + 1)
    {
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
        lifetime--;
    }

    if (lifetime <= 0)
    {
        actionTag = "die";
    }

    // particles->update(sprite->getPosition().x, sprite->getPosition().y);
    //

    Collide();
}

void Shell::sMove()
{
    sprite->move(transform->speedX * deltaTime*gameSpeed, transform->speedY * deltaTime*gameSpeed);
}

void Shell::Collide()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->sprite->getGlobalBounds().intersects(this->sprite->getGlobalBounds()) && entities[i] != this && entities[i]->tag != this->tag && entities[i]->id != ownerID && entities[i]->isProjectile == false && entities[i]->layer == this->layer && gameTime.getElapsedTime().asSeconds() > lastActionFrame + 0.1 && lastTarget != entities[i] && entities[i]->actionTag != "die")
        {
            entities[i]->hurt(dmg);

            lastActionFrame = gameTime.getElapsedTime().asSeconds();
            lastTarget = entities[i];

            float dx = entities[i]->sprite->getPosition().x - sprite->getPosition().x;
            float dy = entities[i]->sprite->getPosition().y - sprite->getPosition().y;

            float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

            entities[i]->sprite->move(dx / l * 20, dy / l * 20);

            this->projectileHealth--;
        }
        // del
        if (projectileHealth <= 0 || lifetime <= 0)
        {
            for (int i = 0; i < entities.size(); i++)
            {
                if (id == entities[i]->id)
                {
                    entities.erase(entities.begin() + i);
                }
            }

            delete this;
            break;
        }
    }
}