#include "../entities/Player.hpp"
#include "../entities/BlueSlime.hpp"
#include "../entities/GreenSlime.hpp"
#include "../entities/LimeSlime.hpp"
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
    std::vector<Entity* > labels;

    Entity* waveCounter;
    Entity* scoreCounter;

    int wave;
    int lastActionFrame;

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

    lastActionFrame = gameTime.getElapsedTime().asSeconds();

    waveCounter = new Entity;
    ui.push_back(waveCounter);
    waveCounter->text = new sf::Text;
    waveCounter->text->setFont(m_fonts["singleday.ttf"]); // font is a sf::Font
    waveCounter->text->setString("Wave 1");
    waveCounter->text->setPosition(WINDOW_W-200, 0);
    waveCounter->text->setCharacterSize(60); // in pixels, not points!
    waveCounter->text->setFillColor(sf::Color::White);

    scoreCounter = new Entity;
    scoreCounter->text = new sf::Text;
    scoreCounter->text->setFont(m_fonts["singleday.ttf"]); // font is a sf::Font
    scoreCounter->text->setString("Score 0");
    scoreCounter->text->setPosition(WINDOW_W-150, 65);
    scoreCounter->text->setCharacterSize(35); // in pixels, not points!
    scoreCounter->text->setFillColor(sf::Color::White);

    ui.push_back(scoreCounter);

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
    mana[0]->sprite->setPosition(sf::Vector2f(m_textures["ui/mp.png"].getSize().x * 4, m_textures["ui/hp.png"].getSize().y * 4));
    ui.push_back(mana[0]);
    mana.push_back(new Mana);
    mana[1]->sprite->setPosition(sf::Vector2f(m_textures["ui/mp.png"].getSize().x * 4 + m_textures["ui/mana.png"].getSize().x * 4, m_textures["ui/hp.png"].getSize().y * 4));
    ui.push_back(mana[1]);
    mana.push_back(new Mana);
    mana[2]->sprite->setPosition(sf::Vector2f(m_textures["ui/mp.png"].getSize().x * 4 + m_textures["ui/mana.png"].getSize().x * 2 * 4, m_textures["ui/hp.png"].getSize().y * 4));
    ui.push_back(mana[2]);
    mana.push_back(new Mana);
    mana[3]->sprite->setPosition(sf::Vector2f(m_textures["ui/mp.png"].getSize().x * 4 + m_textures["ui/mana.png"].getSize().x * 3 * 4, m_textures["ui/hp.png"].getSize().y * 4));
    ui.push_back(mana[3]);

    bg = new Background;
    ui.push_back(bg);

    // Entity* temp = new Entity;
    // temp->text = new sf::Text;
    // temp->text->setFont(m_fonts["singleday.ttf"]); // font is a sf::Font
    // temp->text->setString("Score 0");
    // temp->text->setPosition(WINDOW_W-150, 65);
    // temp->text->setCharacterSize(35); // in pixels, not points!
    // temp->text->setFillColor(sf::Color::White);
    
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
        waveCounter->text->setString("Wave " + std::to_string(wave));
        player->mana=4;
        sSpawnWaves();
    }


    scoreCounter->text->setString("Score " + std::to_string(score));

for(int i=0;i<hearts.size();i++) {
        if(player->health>i) {
             hearts[i]->sprite->setTexture(m_textures["ui/heart.png"]);
        } else {
             hearts[i]->sprite->setTexture(m_textures["ui/empty_heart.png"]);
        }
    }

    for(int i=0;i<mana.size();i++) {
        if(player->mana>i) {
             mana[i]->sprite->setTexture(m_textures["ui/mana.png"]);
        } else {
             mana[i]->sprite->setTexture(m_textures["ui/empty_mana.png"]);
        }
    }

    if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 5 && player->mana<4)
    {
        player->mana++;
        lastActionFrame=gameTime.getElapsedTime().asSeconds();
    }

    if(shake>0) {

        int shakeIntensity;
        if(player->actionTag=="hurt") {
            shakeIntensity=20;
        } else {
            shakeIntensity=10;
        }

        view.setCenter(sf::Vector2f(WINDOW_W / 2 + std::rand()%shakeIntensity, WINDOW_H / 2 + std::rand()%shakeIntensity));
        window.setView(view);
        shake-=gameTime.getElapsedTime().asSeconds()-lastActionFrame;
    } else {
    view.setCenter(sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2));
    window.setView(view);
    }
}

void Scene_Play::sSpawnWaves()
{
    if (wave == 1)
    {
        entities.push_back(new BlueSlime);
        // entities.push_back(new GreenSlime);
        // entities.push_back(new GreenSlime);
        // entities.push_back(new BlueSlime);
        // entities.push_back(new LimeSlime);
        // entities.push_back(new LimeSlime);
        // entities.push_back(new RedSkelWiz);
    }
    else
    {
        entities.push_back(new BlueSlime);
        entities.push_back(new BlueSlime);
        entities.push_back(new BlueSlime);
        // entities.push_back(new BlueSkelWiz);
        entities.push_back(new RedSkelWiz);
    }
}

// void Scene_Play::selectPowerup() {

// }