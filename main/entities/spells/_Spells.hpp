#include "../_Entity.hpp"
#pragma once

class Spells : public Entity, public Projectile
{
public:

    Entity* lastTarget;

    Spells(float originX, float originY, float targetX, float targetY, int id, int damage, int phealth, int life);

    void update(float time);
    // void sAnimate();
    void sMove();

    void Collide();

};

Spells::Spells(float originX, float originY, float targetX, float targetY, int id, int damage=1, int phealth=1, int life=2)
{
    hatesPlayer=false;
    isProjectile = true;
    tag = "Explosion";

    ownerID = id;
    dmg = damage;
    projectileHealth = phealth;
    lifetime=life; // in sec

    lastActionFrame=0;
    lastTarget=NULL;

    sprite = new CSprite(m_textures["spells/explosion/0.png"]);
    sprite->setOrigin(m_textures["spells/explosion/0.png"].getSize().x / 2, m_textures["spells/explosion/0.png"].getSize().y / 2);
    sprite->setPosition(sf::Vector2f(originX, originY));

    // particles = new ParticleSystem(targetX, targetY);

    float dx = targetX - originX;
    float dy = targetY - originY;

    float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

    transform = new CTransform(dx / l * 500, dy / l * 500);

    scale = 1;
}

void Spells::update(float time)
{

    deltaTime = time;
    sMove();

    if(gameTime.getElapsedTime().asSeconds()>lastActionFrame+1) {
        lastActionFrame=gameTime.getElapsedTime().asSeconds();
        lifetime--;
    }

    if(lifetime<=0) {
        actionTag="die";
    }

    // particles->update(sprite->getPosition().x, sprite->getPosition().y);
    //
    

    Collide();
}

void Spells::sMove()
{
    sprite->move(transform->speedX * deltaTime, transform->speedY * deltaTime);
}

void Spells::Collide()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->sprite->getGlobalBounds().intersects(this->sprite->getGlobalBounds()) && entities[i] != this && entities[i]->tag != this->tag && entities[i]->id != ownerID && entities[i]->isProjectile == false && entities[i]->layer == this->layer && gameTime.getElapsedTime().asSeconds() > lastActionFrame + 0.1 && lastTarget!=entities[i])
        {
            entities[i]->hurt(dmg);

            lastActionFrame=gameTime.getElapsedTime().asSeconds();
            lastTarget=entities[i];

            float dx = entities[i]->sprite->getPosition().x - sprite->getPosition().x;
            float dy = entities[i]->sprite->getPosition().y - sprite->getPosition().y;

            float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

            entities[i]->sprite->move(dx/l*20, dy/l*20);

            entities[i]->text = new sf::Text;
            entities[i]->text->setFont(m_fonts["noto.ttf"]); // font is a sf::Font
            entities[i]->text->setString(std::to_string(dmg));
            entities[i]->text->setPosition(entities[i]->sprite->getPosition().x + 24, entities[i]->sprite->getPosition().y + 24);
            entities[i]->text->setCharacterSize(24); // in pixels, not points!
            entities[i]->text->setFillColor(sf::Color::Red);

            this->projectileHealth--;
        }
        // del
        if (projectileHealth <= 0 || lifetime<=0)
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