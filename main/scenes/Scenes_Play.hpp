#include "../entities/Player.hpp"
#include "../entities/Slime.hpp"
#include "../entities/blueSkelWiz.hpp"
#include "../entities/redSkelWiz.hpp"
#include "../entities/Explosion.hpp"

#include "../entities/bg/map.hpp"
#include "../entities/ui/heart.hpp"

#pragma once
class Scene_Play : public Scenes
{
public:
    Entity *player, *hp;

    int wave;
    
    //

    Scene_Play();

    void run(float time);
    void update();
    // systems

    void sSpawnWaves();
};

Scene_Play::Scene_Play()
{
    wave = 0;

    player = new Player;
    entities.push_back(player);

    hp = new Heart;
    hp->text = new sf::Text();
    hp->text->setFont(m_fonts["noto.ttf"]); // font is a sf::Font
    hp->text->setString(std::to_string(player->health));
    hp->text->setPosition(m_textures["ui/heart.png"].getSize().x * 2, 720 - m_textures["ui/heart.png"].getSize().y * 2 - 24);
    hp->text->setCharacterSize(24); // in pixels, not points!
    hp->text->setFillColor(sf::Color::White);
    ui.push_back(hp);
    ui.push_back(new Background);
}

void Scene_Play::run(float time)
{
    deltaTime = time;

    update();
    sRender();
    sEntityUpdate();

    //
}

void Scene_Play::update()
{

    hp->text->setString(std::to_string(player->health));

    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
    }

    if (entities.size() == 1)
    {
        wave++;
        sSpawnWaves();
    }
}

void Scene_Play::sSpawnWaves()
{
    if (wave == 1)
    {
        entities.push_back(new Slime);
        entities.push_back(new Slime);
    }
    else
    {
        entities.push_back(new Slime);
        // entities.push_back(new BlueSkelWiz);
        // entities.push_back(new RedSkelWiz);
    }

    // std::cout << entities.size() << std::endl;
}