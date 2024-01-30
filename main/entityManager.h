#include "components.h"

class Entity
{
public:
    std::string tag;
    int e_id;

    CShape *cshape = NULL;
    CTransform *ctransfrom = NULL;
    CInput *cinput = NULL;

    Entity(std::string t, int id, float radius, float edges, float px, float py, float sx, float sy, bool controllable)
    {
        tag = t;
        e_id = id;
        cshape = new CShape(radius, edges);
        ctransfrom = new CTransform(px, py, sx, sy, 0);
        if (controllable == true)
        {
            cinput = new CInput;
        }
    }
};

class EntityManager
{
public:
    std::vector<Entity *> m_entities;
    int m_totalEntities = 0;

    Entity *addEntities(std::string tag, float px, float py, float sx, float sy, bool controllable = false)
    {
        Entity *ptr = new Entity(tag, m_totalEntities++, 10.f, 10, px, py, sx, sy, controllable);
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
            }
        }
    }

    std::vector<Entity *> getEntities()
    {
        return m_entities;
    }
};