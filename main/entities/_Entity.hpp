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

    float lastActionFrame;
    float scale;

    CSprite *sprite = NULL;
    CTransform *transform = NULL;
    sf::Text *text = NULL;

    float deltaTime;
    std::string actionTag;

    // functions
    Entity();
    ~Entity();

    virtual void update(float time);
    virtual void sAnimate();

    virtual void hurt(int dmg);
};

Entity::Entity()
{
    id = totalEntities++;
    layer = 1;

    direction = 1;
    health = 1;
    actionTag="idle";
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
    if (currentFrame < animationMap[actionTag].size() && gameTime.getElapsedTime().asSeconds() > animationTimer + frameDelay)
    {
        sprite->setTexture(animationMap[actionTag][currentFrame++]);
        animationTimer = gameTime.getElapsedTime().asSeconds();
    }
    else if (currentFrame == animationMap[actionTag].size())
    {
        // if(isTakingDmg)
        animationTimer=gameTime.getElapsedTime().asSeconds()+frameDelay;

        // if (isTakingDmg)
        // {
        //     delete text;
        //     text = NULL;
        // }

        
            currentFrame = 0;
            actionTag="move";

    }
}

void Entity::hurt(int dmg) {
    health-=dmg;
    actionTag="hurt";
}