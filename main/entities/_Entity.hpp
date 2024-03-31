#include "../components/Components.hpp"
#include "../assetManager/assetManager.hpp"
#include "../particles.hpp"
#include "_Animated.hpp"
#include "_States.hpp"
#include "_Projectile.hpp"
#include "_Hostile.hpp"

#pragma once

int totalEntities = 0;

class Entity : public Animated
{

public:
    std::map<std::string, std::vector<sf::Texture>> animationMap;

    std::string tag;
    int id;
    int layer;

    int health;
    int mana;

    float lastActionFrame;
    float scale;

    bool hatesPlayer;
    bool isProjectile;

    CSprite *sprite = NULL;
    CTransform *transform = NULL;
    sf::Text *text = NULL;
    ParticleSystem *particles = NULL;

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
    actionTag = "idle";

    isProjectile = false;
    lastActionFrame=gameTime.getElapsedTime().asSeconds();
}
Entity::~Entity()
{
    delete sprite;
    delete transform;
    delete text;
    delete particles;
}

void Entity::update(float time)
{
    //
}

void Entity::sAnimate()
{
    if(actionTag == "die") {
        // std::cout<<"a"<<std::endl;
        return;
    }
    if (health <= 0)
    {
        actionTag = "die";
        sprite->setTexture(animationMap[actionTag][0]);
        animationTimer = gameTime.getElapsedTime().asSeconds();
        return;
    }

    if (animationMap[actionTag].size() == 1)
    {
        sprite->setTexture(animationMap[actionTag][0]);
        actionTag = "move";
        currentFrame=0;
        animationTimer = gameTime.getElapsedTime().asSeconds();
        return;
    }

    if (currentFrame < animationMap[actionTag].size() && gameTime.getElapsedTime().asSeconds() > animationTimer + frameDelay)
    {
        sprite->setTexture(animationMap[actionTag][currentFrame++]);
        animationTimer = gameTime.getElapsedTime().asSeconds();
        return;
    }
    else if (currentFrame == animationMap[actionTag].size())
    {
        animationTimer = gameTime.getElapsedTime().asSeconds();
        currentFrame = 0;
        actionTag = "move";

        if (actionTag == "hurt")
        {
            delete text;
            text = nullptr;
        }
    }
}

void Entity::hurt(int dmg)
{
    health -= dmg;
    actionTag = "hurt";
}