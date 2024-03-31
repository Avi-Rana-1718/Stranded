#include "../_Entity.hpp"
#pragma once

class Spells : public Entity, public Projectile
{
public:
    Spells(float originX, float originY, float targetX, float targetY, int id);

    void update(float time);
    // void sAnimate();
    void sMove();

    void Collide();
};

Spells::Spells(float originX, float originY, float targetX, float targetY, int id)
{

    isProjectile = true;
    tag = "Explosion";

    ownerID = id;
    dmg = 1;
    projectileHealth = 1;
    lifetime=144;
    // projectileDuration=5;
    // knockback=;

    sprite = new CSprite(m_textures["spells/explosion/0.png"]);
    sprite->setOrigin(m_textures["spells/explosion/0.png"].getSize().x / 2, m_textures["spells/explosion/0.png"].getSize().y / 2);
    sprite->setPosition(sf::Vector2f(originX, originY));

    particles = new ParticleSystem(targetX, targetY);

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

    if(lifetime--<=0) {
        actionTag="die";
    }

    particles->update(sprite->getPosition().x, sprite->getPosition().y);

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
        if (entities[i]->sprite->getGlobalBounds().intersects(this->sprite->getGlobalBounds()) && entities[i] != this && entities[i]->tag != this->tag && entities[i]->id != ownerID && entities[i]->isProjectile == false && entities[i]->layer == this->layer)
        {
            entities[i]->hurt(dmg);

            float offsetX = (std::rand()) / 1000 * 10 * 10;
            float offsetY = (std::rand()) / 1000 * 10 * 10;

            view.setCenter(view.getCenter() + sf::Vector2f(offsetX, offsetY));

            entities[i]->text = new sf::Text;
            entities[i]->text->setFont(m_fonts["noto.ttf"]); // font is a sf::Font
            entities[i]->text->setString(std::to_string(dmg));
            entities[i]->text->setPosition(entities[i]->sprite->getPosition().x + 24, entities[i]->sprite->getPosition().y + 24);
            entities[i]->text->setCharacterSize(24); // in pixels, not points!
            entities[i]->text->setFillColor(sf::Color::Red);

            this->projectileHealth--;
        }
        // del
        if (projectileHealth <= 0)
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