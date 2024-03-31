#include "../entities/Player.hpp"
#include "../entities/Slime.hpp"
#include "../entities/blueSkelWiz.hpp"
#include "../entities/redSkelWiz.hpp"
#include "../entities/Explosion.hpp"

#include "../entities/bg/map.hpp"
#include "../entities/ui/heart.hpp"
#include "../entities/ui/hp.hpp"
#include "../entities/ui/mana.hpp"
#include "../entities/ui/mp.hpp"
#pragma once
class Scene_Play : public Scenes
{
public:
    Entity *player;
    std::vector<Heart *> hearts;
    std::vector<Mana *> mana;

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
    ui.push_back(new HP);
    ui.push_back(new MP);


    hearts.push_back(new Heart);
    hearts[0]->sprite->setPosition(sf::Vector2f(m_textures["ui/hp.png"].getSize().x * 4, 0));
    ui.push_back(hearts[0]);
    hearts.push_back(new Heart);
    hearts[1]->sprite->setPosition(sf::Vector2f(m_textures["ui/hp.png"].getSize().x * 4 + m_textures["ui/heart.png"].getSize().x * 4, 0));
    ui.push_back(hearts[1]);
    hearts.push_back(new Heart);
    hearts[2]->sprite->setPosition(sf::Vector2f(m_textures["ui/hp.png"].getSize().x * 4 + m_textures["ui/heart.png"].getSize().x * 2 * 4, 0));
    ui.push_back(hearts[2]);
    hearts.push_back(new Heart);
    hearts[3]->sprite->setPosition(sf::Vector2f(m_textures["ui/hp.png"].getSize().x * 4 + m_textures["ui/heart.png"].getSize().x * 3 * 4, 0));
    ui.push_back(hearts[3]);

    mana.push_back(new Mana);
    mana[0]->sprite->setPosition(sf::Vector2f(m_textures["ui/mp.png"].getSize().x * 4, m_textures["ui/hp.png"].getSize().y*4));
    ui.push_back(mana[0]);
    mana.push_back(new Mana);
    mana[1]->sprite->setPosition(sf::Vector2f(m_textures["ui/mp.png"].getSize().x * 4 + m_textures["ui/mana.png"].getSize().x * 4, m_textures["ui/hp.png"].getSize().y*4));
    ui.push_back(mana[1]);
    mana.push_back(new Mana);
    mana[2]->sprite->setPosition(sf::Vector2f(m_textures["ui/mp.png"].getSize().x * 4 + m_textures["ui/mana.png"].getSize().x * 2 * 4, m_textures["ui/hp.png"].getSize().y*4));
    ui.push_back(mana[2]);
    mana.push_back(new Mana);
    mana[3]->sprite->setPosition(sf::Vector2f(m_textures["ui/mp.png"].getSize().x * 4 + m_textures["ui/mana.png"].getSize().x * 3 * 4, m_textures["ui/hp.png"].getSize().y*4));
    ui.push_back(mana[3]);

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

    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
    }

    if (entities.size() == 1)
    {
        wave++;
        sSpawnWaves();
    }

    if (player->health <= 3)
    {
        hearts[3]->sprite->setTexture(m_textures["ui/empty_heart.png"]);
    }
    if (player->health <= 2)
    {
        hearts[2]->sprite->setTexture(m_textures["ui/empty_heart.png"]);
    }
    if (player->health <= 1)
    {
        hearts[1]->sprite->setTexture(m_textures["ui/empty_heart.png"]);
    }
    if(player->health<=0)
    {
        hearts[0]->sprite->setTexture(m_textures["ui/empty_heart.png"]);
    }

    if (player->mana <= 3)
    {
        mana[3]->sprite->setTexture(m_textures["ui/empty_mana.png"]);
    }
    if (player->mana <= 2)
    {
        mana[2]->sprite->setTexture(m_textures["ui/empty_mana.png"]);
    }
    if (player->mana <= 1)
    {
        mana[1]->sprite->setTexture(m_textures["ui/empty_mana.png"]);
    }
    if(player->mana<=0)
    {
        mana[0]->sprite->setTexture(m_textures["ui/empty_mana.png"]);
    }
}

void Scene_Play::sSpawnWaves()
{
    if (wave == 1)
    {
        entities.push_back(new Slime);
        entities.push_back(new Slime);
        entities.push_back(new RedSkelWiz);
    }
    else
    {
        // entities.push_back(new Slime);
        // entities.push_back(new BlueSkelWiz);
        entities.push_back(new RedSkelWiz);
    }
}