#include "components.h"

class Entity
{

public:
    std::string tag;
    int w, h;
    float scale = 4.f;
    int direction = 1;

    int e_id;
    int e_health;

    CTransform *ctransform = NULL;
    CSprite *csprite = NULL;
    CText *ctext = NULL;
    sf::RectangleShape *cshape = NULL;

    bool controllable;
    bool collision;
    bool stationary;
    bool animated;

    int currentFrame;
    int animationDelay;
    int animationTimer;

    bool isMoving;
    bool isAttacking;

    Entity(std::string t, int id, float width, float height, float px, float py, sf::Texture &texture)
    {
        tag = t;
        e_id = id;
        e_health = 1;

        w = width * scale;
        h = height * scale;

        direction = 1;

        csprite = new CSprite(texture);
        csprite->setPosition(px, py);
        csprite->setScale(sf::Vector2f(scale, scale));
        csprite->setOrigin(sf::Vector2f(width / 2, height / 2));

        controllable = false;
        collision = true;
        stationary = true;
        animated = false;

        currentFrame = 0;
        animationDelay = 7;
        animationTimer = 0;

        isMoving = false;
        isAttacking = false;
    }

    ~Entity()
    {
        delete ctransform;
        delete csprite;
        delete ctext;
        delete cshape;
    }

    float getLeft()
    {
        return csprite->getPosition().x - w / 2;
    }

    float getRight()
    {
        return csprite->getPosition().x + w / 2;
    }

    float getTop()
    {
        return csprite->getPosition().y - h / 2;
    }

    float getBottom()
    {
        return csprite->getPosition().y + h / 2;
    }

    void sAnimate(std::map<std::string, std::vector<sf::Texture *>> textures, int frames)
    {

        if (controllable)
        {
            isMoving = (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D));
            isAttacking = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        }

        // direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            direction = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            direction = 1;
        }

        csprite->setScale(sf::Vector2f(direction * scale, scale));

        // move

        std::string animationType;
        if (isAttacking)
        {
            animationType = "attack";
        }
        else if (isMoving)
        {
            animationType = "move";
        }
        else
        {
            animationType = "idle";
        }

        if (animationType != "idle")
        {
            if (frames >= animationDelay + animationTimer)
            {
                csprite->setTexture(*textures[tag + "/" + animationType][currentFrame++]);
                animationTimer = frames;

                if (currentFrame == textures[tag + "/" + animationType].size())
                {
                    currentFrame = 0;
                    animationTimer = frames + animationDelay;
                }
            }
        }
        else
        {
            csprite->setTexture(*textures[tag + "/" + animationType][0]);
        }
    }
};

class EntityManager
{
public:
    std::vector<Entity *> m_entities;
    int m_totalEntities = 0;

    Entity *addEntities(std::string tag, sf::Texture &texture)
    {
        int px = m_totalEntities * 300 + 100;
        int py = std::rand() % (550 - 100 + 1) + 100;

        Entity *ptr = new Entity(tag, m_totalEntities++, texture.getSize().x, texture.getSize().y, px, py, texture);
        m_entities.push_back(ptr);
        return ptr;
    }

    void removeEntity(int id)
    {
        for (int i = 0; i < m_entities.size(); i++)
        {
            if (m_entities[i]->e_id == id)
            {
                delete (m_entities.at(i));
                m_entities.erase(m_entities.begin() + i);
                break;
            }
        }
    }

    void clearEntities()
    {
        for (auto entity : m_entities)
        {
            delete entity;
        }
        m_entities.erase(m_entities.begin(), m_entities.end());
    }

    std::vector<Entity *> &getEntities()
    {
        return m_entities;
    }
};