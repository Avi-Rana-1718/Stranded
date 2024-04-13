#include "../components/Components.hpp"
#include "../assetManager/assetManager.hpp"
#include "../particles.hpp"
#include "_Animated.hpp"
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

    float lastActionFrame;
    float scale;

    bool hatesPlayer;
    bool isProjectile;
    bool honour;
    bool isInvulnerable;

    CSprite *sprite = NULL;
    CTransform *transform = NULL;
    sf::Text *text = NULL;
    sf::RectangleShape *shape = NULL;
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

    direction = "";
    health = 1;
    actionTag = "idle";
    rotate=1;

    hatesPlayer=false;
    isProjectile = false;
    honour=false;
    isInvulnerable=false;

    scale=1;

    lastActionFrame=gameTime.getElapsedTime().asSeconds();
}
Entity::~Entity()
{
    delete sprite;
    delete transform;
    delete text;
    delete shape;
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
        score++;
        std::cout<<score<<std::endl;
        return;
    }

    if (animationMap[actionTag].size() == 1)
    {
        sprite->setTexture(animationMap[actionTag][0]);
        actionTag = "idle";
        currentFrame=0;
        animationTimer = gameTime.getElapsedTime().asSeconds();
        return;
    }
    if(actionTag=="move" && direction.length()!=0) {
        actionTag+="-";
        if(direction=="left"||direction=="right")
        actionTag+="horizontal";
        else
        actionTag+=direction;
    }

    if(direction=="right") {
        rotate=1;
    } else if(direction=="left") {
        rotate=-1;
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
        actionTag = "idle";

        if (actionTag == "hurt")
        {
            delete text;
            text = nullptr;
        }
    }
}

void Entity::hurt(int dmg)
{
    if(isInvulnerable==false) {
    health -= dmg;
    actionTag = "hurt";
    shake=10;

    if(honour==true) {
        honour=false;
    }

    sound.setBuffer(m_sounds["hurt.wav"]);
    sound.play();   

    }
    
}