#include "entityManager.h"
#include "vector2.h"

// Constants

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 720


class Game {
    sf::RenderWindow window;
    EntityManager entities;

    void SDraw(const std::vector<Entity*>& entities);

    public:

    Entity* player;
        Game() {
            window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
            window.setFramerateLimit(60);
        }

        void run() {
                //declarations
    entities.addEntities("Player");
    entities.addEntities("Enemy");

    while(1) {
            SDraw(entities.getEntities());
    }

        };
};

void Game::SDraw(const std::vector<Entity*>& entities) {
    std::cout<<std::endl<<entities.size();
            window.clear();
    for(int i=0;i<entities.size();i++) {
        window.draw(entities[i]->cshape->circle);
    }
            window.display();
}