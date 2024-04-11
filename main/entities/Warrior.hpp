#include "_Entity.hpp"

class Warrior : public Entity, public Hostile
{
public:
    Warrior();
    Entity *target = NULL;


    // functions
    void update(float time);

    void sMove();
    void sAttack();
};

Warrior::Warrior()
{
    hatesPlayer = true;
    target = entities[0];

    tag = "Warrior";
    health = 3;

    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    attackDmg = 1;

    if(1) {
        honour=true;
    }

    //
    animationMap["idle"].push_back(m_textures["warrior/idle0.png"]);
    animationMap["idle"].push_back(m_textures["warrior/idle1.png"]);
    animationMap["idle"].push_back(m_textures["warrior/idle2.png"]);
    animationMap["idle"].push_back(m_textures["warrior/idle3.png"]);
    animationMap["idle"].push_back(m_textures["warrior/idle4.png"]);

    animationMap["move"].push_back(m_textures["warrior/idle0.png"]);
    animationMap["move"].push_back(m_textures["warrior/idle1.png"]);
    animationMap["move"].push_back(m_textures["warrior/idle2.png"]);
    animationMap["move"].push_back(m_textures["warrior/idle3.png"]);
    animationMap["move"].push_back(m_textures["warrior/idle4.png"]);

    animationMap["hurt"].push_back(m_textures["warrior/hit.png"]);

    animationMap["attack"].push_back(m_textures["warrior/attack0.png"]);
    animationMap["attack"].push_back(m_textures["warrior/attack1.png"]);
    animationMap["attack"].push_back(m_textures["warrior/attack2.png"]);
    animationMap["attack"].push_back(m_textures["warrior/attack3.png"]);
    animationMap["attack"].push_back(m_textures["warrior/attack4.png"]);

    animationMap["die"].push_back(m_textures["warrior/die0.png"]);
    // animationMap["die"].push_back(m_textures["warrior/die1.png"]);
    // animationMap["die"].push_back(m_textures["warrior/die2.png"]);
    // animationMap["die"].push_back(m_textures["warrior/die3.png"]);
    // animationMap["die"].push_back(m_textures["warrior/die4.png"]);
    // animationMap["die"].push_back(m_textures["warrior/die5.png"]);
    // animationMap["die"].push_back(m_textures["warrior/die6.png"]);
    // animationMap["die"].push_back(m_textures["warrior/die7.png"]);

    sprite = new CSprite(m_textures["warrior/idle0.png"]);
    sprite->setPosition(sf::Vector2f((rand() % WINDOW_W - 100) + 100, (rand() % WINDOW_H - 100) + 100));
    sprite->setOrigin(m_textures["warrior/idle0.png"].getSize().x / 2, m_textures["warrior/idle0.png"].getSize().y / 2);
    transform = new CTransform(150, 150);

    scale = 4;

    actionTag = "idle";
}

void Warrior::update(float time)
{
    deltaTime = time;
    sAnimate();
    sAttack();
    sMove();
}

void Warrior::sMove()
{

    if (actionTag != "die" && actionTag != "hurt" && actionTag != "attack")
    {
        actionTag = "move";
    }

    if (actionTag != "die" && actionTag != "attack")
    {
          int f = 1;
        if(honour==true) {
        for (int i = 0; i < entities.size(); i++)
        {
            if (entities[i]->tag == "Guard")
            {
                f = 0;
                break;
            }
        }
        }

        float dx = target->sprite->getPosition().x - sprite->getPosition().x;
        float dy = target->sprite->getPosition().y - sprite->getPosition().y;
        float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

        if (f)
        {
            sprite->move((dx / l) * deltaTime * transform->speedX, (dy / l) * deltaTime * transform->speedY);
        }
    }
}

void Warrior::sAttack()
{

    if (target->sprite->getPosition().x - sprite->getPosition().x > 0)
    {
        rotate = 1;
    }
    else
    {
        rotate = -1;
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
