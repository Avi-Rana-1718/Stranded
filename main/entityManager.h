#include "components.h"

class Entity
{
public:
    std::string tag;
    int e_id;

    CShape *cshape = NULL;
    CTransform *ctransform = NULL;
    
    int e_health;

    bool controllable = false;

    Entity(std::string t, int id, float w, float h, float px, float py, float sx, float sy, sf::Color color, sf::Color outline_color, int outline_thickness, bool controll)
    {
        tag = t;
        e_id = id;
        e_health=1;
        cshape = new CShape(w, h, color, outline_color, outline_thickness);
        ctransform = new CTransform(px, py, sx, sy, 0);
        controllable=controll;
    }

    ~ Entity() {
        delete cshape;
        delete ctransform;
    }
};

class EntityManager
{
public:
    std::vector<Entity *> m_entities;
    int m_totalEntities = 0;

    Entity *addEntities(std::string tag, float w, float h, float px, float py, float sx, float sy, sf::Color color, sf::Color outline = sf::Color(255, 255, 255), int outline_thickness = 0, bool controllable = false)
    {
        Entity *ptr = new Entity(tag, m_totalEntities++, w, h, px, py, sx, sy, color, outline, outline_thickness, controllable);
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