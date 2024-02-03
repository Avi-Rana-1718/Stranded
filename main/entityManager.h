#include "components.h"

class Entity
{

public:
    std::string tag;
    int e_id;

    CTransform *ctransform = NULL;
    CSprite *csprite = NULL;

    int e_health;

    int w, h;

    float scale=3.f;

    bool controllable = false;

    Entity(std::string t, int id, float width, float height, float px, float py, float sx, float sy, bool controll, sf::Texture &texture)
    {
        tag = t;
        e_id = id;
        e_health = 1;

        w = width*scale;
        h = height*scale;

        if (px != 0 && py != 0 && sx != 0 && sy != 0)
        {
            ctransform = new CTransform(px, py, sx, sy, 0);
        }
        csprite = new CSprite(texture);

        controllable = controll;
    }

    ~Entity()
    {
        delete ctransform;
        delete csprite;
    }
};

class EntityManager
{
public:
    std::vector<Entity *> m_entities;
    int m_totalEntities = 0;

    Entity *addEntities(std::string tag, float sx, float sy, sf::Texture &texture, bool controllable = false)
    {

        int px = (rand() % (1700 - 100) + 100);
        int py = (rand() % (600 - 100) + 100);

        Entity *ptr = new Entity(tag, m_totalEntities++, texture.getSize().x, texture.getSize().y, px, py, sx, sy, controllable, texture);
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

    std::vector<Entity *> getEntities()
    {
        return m_entities;
    }
};