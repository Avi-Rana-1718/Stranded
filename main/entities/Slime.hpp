#include "_Entity.hpp"

class Slime : public Entity, public Hostile
{
public:
    Slime();
    Entity *target = NULL;

    // functions
    void update(float time);

    void sMove();
    void sAttack();
};

Slime::Slime()
{
    hatesPlayer = true;
    target=entities[0];

    tag = "Slime";
    health = 3;

    frameDelay = 0.25;
    animationTimer = 0;
    currentFrame = 0;

    attackDmg = 1;

    //
    animationMap["move"].push_back(m_textures["slime/large/move0.png"]);
    animationMap["move"].push_back(m_textures["slime/large/move1.png"]);
    animationMap["move"].push_back(m_textures["slime/large/move2.png"]);
    animationMap["attack"].push_back(m_textures["slime/large/move1.png"]);
    animationMap["hurt"].push_back(m_textures["slime/large/hit.png"]);
    animationMap["die"].push_back(m_textures["slime/large/die.png"]);

    sprite = new CSprite(m_textures["slime/large/move0.png"]);
    sprite->setPosition(sf::Vector2f((rand() % 1000 - 100) + 100, (rand() % 500 - 100) + 100));
    transform = new CTransform(120, 120);

    scale = 3;

    actionTag="move";
}

void Slime::update(float time)
{
    deltaTime = time;
    sAnimate();
    sAttack();
    sMove();
}

void Slime::sMove()
{

    actionTag=((actionTag!="attack")||(actionTag!="hurt"))?"move":"hurt";
    float dx = target->sprite->getPosition().x - sprite->getPosition().x;
    float dy = target->sprite->getPosition().y - sprite->getPosition().y;
    float l = pow(pow(dx, 2) + pow(dy, 2), 0.5);

    sprite->move((dx / l) * deltaTime * transform->speedX, (dy / l) * deltaTime * transform->speedY);
    
}

void Slime::sAttack()
{
    if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 1 && sprite->getGlobalBounds().intersects(target->sprite->getGlobalBounds()))
    {
        actionTag="attack";
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
        target->hurt(attackDmg);
    }
}
