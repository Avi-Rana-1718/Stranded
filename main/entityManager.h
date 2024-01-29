#include "components.h"

class Entity {
public:
std::string tag;
int e_id;

CShape* cshape;


Entity(std::string t, int id, float radius, float edges) {
    tag=t;
    e_id=id;
    cshape = new CShape(radius, edges);
}

};


class EntityManager {
    public:
    std::vector<Entity*> m_entities;
    int m_totalEntities = 0;
    void addEntities(std::string tag) {
            Entity* ptr = new Entity(tag ,m_totalEntities++, 10.f, 10);
            m_entities.push_back(ptr);
    }

    void removeEntity(int id) {
        for(int i=0;i<m_entities.size();i++) {
            if(m_entities[i]->e_id==id) {
                delete(m_entities.at(i));
                m_entities.erase(m_entities.begin()+i);
            }
        }
    }

    std::vector<Entity*> getEntities() {
        return m_entities;
    }

};