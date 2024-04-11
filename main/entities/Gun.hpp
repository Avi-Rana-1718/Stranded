#include "_Entity.hpp"

class Gun : public Entity {

public:
   Gun(Entity* temp);

   Entity* player;


    // functions
    void update(float time);


};

Gun::Gun(Entity* temp) {

    player=temp;
    health=1;
    
    tag="Gun";

    sprite = new CSprite(m_textures["gun.png"]);
    scale = 4.5;
    layer=0;
}

void Gun::update(float time) {
    deltaTime=time;
    int dx = sf::Mouse::getPosition().x - sprite->getPosition().x;
    int dy = sf::Mouse::getPosition().y - sprite->getPosition().y;

    float rotation = (atan2(dy, dx)) * 180 / 3.1421;

    if(dx<0) {
        sprite->setScale(scale, scale*-1);
    } 

    sprite->setRotation(rotation);
    sprite->setPosition(player->sprite->getPosition().x, player->sprite->getPosition().y);
}