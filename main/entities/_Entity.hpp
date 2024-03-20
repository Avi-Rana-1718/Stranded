#include "../components/Components.hpp"
#include "../assetManager/assetManager.hpp"
#include "_Animated.hpp"
#include "_States.hpp"
#include "_Projectile.hpp"
#include "_Hostile.hpp"

#pragma once

int totalEntities = 0;

class Entity : public States, public Animated
{

public:
    std::map<std::string, std::vector<sf::Texture>> animationMap;

    std::string tag;
    int id;
    int layer;

    int health;

    int lastActionFrame;
    float scale;

    CSprite *sprite = NULL;
    CTransform *transform = NULL;
    sf::Text *text = NULL;

    float deltaTime;

    // functions
    Entity();
    ~Entity();

    virtual void update(float time);
    virtual void sAnimate();
};

Entity::Entity()
{
    id = totalEntities++;
    layer = 1;

    direction = 1;
    health = 1;
}
Entity::~Entity()
{
    delete sprite;
    delete transform;
    delete text;
}

void Entity::update(float time)
{
}

void Entity::sAnimate()
{
    std::string actionTag;

    if (isDead)
    {
        actionTag = "die";
    }
    else if (isTakingDmg)
    {
        actionTag = "hurt";
    }
    else if (isAttacking)
    {
        actionTag = "attack";
    }
    else if (isMoving)
    {
        actionTag = "move";
    }
    else
    {
        actionTag = "idle";
    }

    if (isProjectile)
    {
        actionTag = "explode";
    }

    if (currentFrame < animationMap[actionTag].size() && gameTime.getElapsedTime().asSeconds() > animationTimer + frameDelay)
    {
        sprite->setTexture(animationMap[actionTag][currentFrame++]);
        animationTimer = gameTime.getElapsedTime().asSeconds();
    }
    else if (currentFrame == animationMap[actionTag].size())
    {
        // animationTimer = gameTime.getElapsedTime().asSeconds();

        if (isTakingDmg)
        {
            delete text;
            text = NULL;
        }

        if (!isProjectile)
            currentFrame = 0;

        isAttacking = false;
        isTakingDmg = false;
    }
}