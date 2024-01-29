#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// Constants

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 720

// Components



class Entity {
public:
std::string tag;
int e_id;

Entity(std::string t, int id) {
    tag=t;
    e_id=id;
}

};


class EntityManager {
    public:
    std::vector<Entity*> m_entities;
    int m_totalEntities = 0;
    void addEntities(std::string tag) {
            Entity* ptr = new Entity(tag ,m_totalEntities++);
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
        for(int i=0;i<m_entities.size();i++) {
            std::cout<<m_entities.at(i)->tag;
        }
        return m_entities;
    }

};

// class Player : sf::RectangleShape {

//     public:
//     Player(x, y):RectangleShape(sf::Vector2f(x, y)) {

//     }
// }

// Systems

// void sDraw(const std::vector<Entity*> entities) {
//     for(int i=0;i<entities.size();i++) {
//         window.draw(entities.at(i));
//     }
// }



int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    window.setFramerateLimit(60);


    //declarations
    EntityManager e_manager;
    e_manager.addEntities("Player");
    e_manager.addEntities("Enemy");
    e_manager.getEntities();
    e_manager.removeEntity(1);
    e_manager.getEntities();



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // sDraw(e_manager.getEntities);
        window.display();
    }

    return 0;
}