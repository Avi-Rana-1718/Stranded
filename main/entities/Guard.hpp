#include "_Entity.hpp"

class Guard : public Entity, public Hostile
{
public:
    Guard();
    Entity *target = NULL;

    // functions
    void update(float time);

    void sMove();
    void sAttack();
};

Guard::Guard()
{
    hatesPlayer = true;
    target = entities[0];

    tag = "Guard";
    health = 3;

    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    attackDmg = 1;

    //
    animationMap["idle"].push_back(m_textures["guard/idle0.png"]);
    animationMap["idle"].push_back(m_textures["guard/idle1.png"]);
    animationMap["idle"].push_back(m_textures["guard/idle2.png"]);
    animationMap["idle"].push_back(m_textures["guard/idle3.png"]);
    animationMap["idle"].push_back(m_textures["guard/idle4.png"]);

    animationMap["move"].push_back(m_textures["guard/idle0.png"]);
    animationMap["move"].push_back(m_textures["guard/idle1.png"]);
    animationMap["move"].push_back(m_textures["guard/idle2.png"]);
    animationMap["move"].push_back(m_textures["guard/idle3.png"]);
    animationMap["move"].push_back(m_textures["guard/idle4.png"]);

    animationMap["attack"].push_back(m_textures["guard/attack0.png"]);
    animationMap["attack"].push_back(m_textures["guard/attack1.png"]);
    animationMap["attack"].push_back(m_textures["guard/attack2.png"]);
    animationMap["attack"].push_back(m_textures["guard/attack3.png"]);
    animationMap["attack"].push_back(m_textures["guard/attack4.png"]);

    animationMap["die"].push_back(m_textures["guard/die0.png"]);


    sprite = new CSprite(m_textures["guard/idle0.png"]);
    sprite->setPosition(sf::Vector2f((rand() % WINDOW_W - 100) + 100, (rand() % WINDOW_H - 100) + 100));
    sprite->setOrigin(m_textures["guard/idle0.png"].getSize().x/2, m_textures["guard/idle0.png"].getSize().y/2);
    transform = new CTransform(120, 120);

    scale = 3.5;

    actionTag = "idle";
}

void Guard::update(float time)
{
    deltaTime = time;
    sAnimate();
    sAttack();
    sMove();
}

void Guard::sMove()
{

    if (actionTag != "die" && actionTag != "hurt" && actionTag != "attack")
    {
        actionTag = "move";
    }

    if(actionTag!="die" && actionTag!="attack") {
    float dx = target->sprite->getPosition().x - sprite->getPosition().x;
    float dy = target->sprite->getPosition().y - sprite->getPosition().y;
    float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

    sprite->move((dx / l) * deltaTime * transform->speedX, (dy / l) * deltaTime * transform->speedY);
    }
}

void Guard::sAttack()
{

    if(target->sprite->getPosition().x - sprite->getPosition().x > 0) {
        rotate=1;
    } else {
        rotate=-1;
    }


    if (actionTag == "attack" && currentFrame == animationMap["attack"].size() - 1 && sprite->getGlobalBounds().intersects(target->sprite->getGlobalBounds()) && gameTime.getElapsedTime().asSeconds() > lastActionFrame)
    {
        target->hurt(attackDmg);
        lastActionFrame = gameTime.getElapsedTime().asSeconds() + 1;
    }
    else if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 1 && sprite->getGlobalBounds().intersects(target->sprite->getGlobalBounds()) && actionTag != "hurt" && actionTag != "die")
    {
        actionTag = "attack";
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
    }
}
