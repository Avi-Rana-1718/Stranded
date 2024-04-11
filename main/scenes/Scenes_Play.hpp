#include "../entities/Player.hpp"
#include "../entities/Guard.hpp"
#include "../entities/Warrior.hpp"
#include "../entities/Archer.hpp"

#include "../entities/Gun.hpp"
#include "../entities/bg/map.hpp"
#include "../entities/ui/heart.hpp"
#include "../entities/ui/hp.hpp"
#include "../entities/ui/mana.hpp"
#include "../entities/ui/mp.hpp"
#include "../entities/ui/crosshair.hpp"
#pragma once

class Scene_Play : public Scenes
{
public:
    Entity *player, *crosshair, *health, *par;

    // ui elements
    Entity *waveCounter;
    Entity *scoreCounter;
    Entity *annoucementText;

    Entity* b1, b2, b3;

    // announcementConfig
    bool showAnnoucement = true;
    std::string msg = "WAVE CLEARED!";

    float lastActionFrame;


    void init();
    void run(float time);
    void update();
    // systems

    void sSpawnWaves();
    void sSelectBuff();
};

void Scene_Play::init()
{

    Scenes::init();
    window.setMouseCursorVisible(false);

    wave = 0;
    score = 0;

    lastActionFrame = gameTime.getElapsedTime().asSeconds();

    // ui setup
    waveCounter = new Entity;
    ui.push_back(waveCounter);
    waveCounter->text = new sf::Text;
    waveCounter->text->setFont(m_fonts["epilogue.ttf"]);
    waveCounter->text->setString("WAVE 1");
    waveCounter->text->setStyle(sf::Text::Bold);
    waveCounter->text->setCharacterSize(35);
    waveCounter->text->setPosition(WINDOW_W - waveCounter->text->getGlobalBounds().getSize().x - 30, 10);
    waveCounter->text->setFillColor(sf::Color::White);

    scoreCounter = new Entity;
    scoreCounter->text = new sf::Text;
    scoreCounter->text->setFont(m_fonts["epilogue.ttf"]);
    scoreCounter->text->setString("SCORE 0");
    scoreCounter->text->setStyle(sf::Text::Bold);
    scoreCounter->text->setCharacterSize(15);
    scoreCounter->text->setPosition(WINDOW_W - scoreCounter->text->getGlobalBounds().getSize().x - 30, waveCounter->text->getGlobalBounds().getSize().y + 25);
    scoreCounter->text->setFillColor(sf::Color(240, 237, 237));

    ui.push_back(scoreCounter);

    player = new Player;
    entities.push_back(player);
    entities.push_back(new Gun(player));
    Entity *temp = new HP;
    ui.push_back(temp);

    // health = new Entity;
    // health->text = new sf::Text;
    // health->text->setFont(m_fonts["epilogue.ttf"]); // font is a sf::Font
    // // health->text->setStyle(sf::Text::Bold);
    // health->text->setString(std::to_string(player->health));
    // health->text->setPosition(20 + temp->sprite->getGlobalBounds().getSize().x  + temp->sprite->getPosition().x + 50, 10);
    // health->text->setCharacterSize(55); // in pixels, not points!
    // health->text->setFillColor(sf::Color::White);
    // ui.push_back(health);

    bg = new Background;
    background.push_back(bg);

    annoucementText = new Entity;
    annoucementText->text = new sf::Text;
    annoucementText->text->setFont(m_fonts["technicality.ttf"]); // font is a sf::Font
    // annoucementText->text->setStyle(sf::Text::Bold);
    annoucementText->text->setString("Wave cleared");
    annoucementText->text->setOutlineColor(sf::Color(40, 40, 40));
    annoucementText->text->setOutlineThickness(1.5);
    annoucementText->text->setCharacterSize(50); // in pixels, not points!
    annoucementText->text->setOrigin(annoucementText->text->getGlobalBounds().getSize().x / 2, annoucementText->text->getGlobalBounds().getSize().y / 2);
    annoucementText->text->setPosition(WINDOW_W / 2, 50);
    annoucementText->text->setFillColor(sf::Color::White);
    annoucementText->text->setString("");
    ui.push_back(annoucementText);

    // entities.push_back(new Archer);

    crosshair = new Crosshair;
    ui.push_back(crosshair);

    // colors.push_back(sf::Color(255, 0, 0));
    // colors.push_back(sf::Color(255, 127, 0));
    // colors.push_back(sf::Color(255, 255, 0));
    // colors.push_back(sf::Color(0, 255, 0));
    // colors.push_back(sf::Color(0, 0, 255));
    // colors.push_back(sf::Color(75, 0, 130));
    // colors.push_back(sf::Color(143, 0, 255));

    par = new Entity;
    par->particles = new ParticleSystem(WINDOW_W, WINDOW_W);
    ui.push_back(par);

    b1 = new Button("", "");
    b1->text->setPosition(WINDOW_W*1/3, WINDOW_H/2);
    ui.push_back(b1);

}

void Scene_Play::run(float time)
{
    deltaTime = time;

    update();
    sRender();
    sEntityUpdate();

    par->particles->update(-100, -100);
    //
}

void Scene_Play::update()
{

    // if(player && player->health==0) {
    // //    delete currentScene;
    //     currentScene = scenes["over"];
    //     currentScene->init();
    // }

    if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 0.1 && showAnnoucement)
    {
        annoucementText->text->setFillColor(sf::Color(255, 255, 255, 255));
        annoucementText->text->setString(annoucementText->text->getString() + msg.front());
        annoucementText->text->setOrigin(annoucementText->text->getGlobalBounds().getSize().x / 2, annoucementText->text->getGlobalBounds().getSize().y / 2);
        // annoucementText->text->setFw
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
        msg.erase(msg.begin());
        if (msg.empty())
        {
            showAnnoucement = false;
            annoucementText->text->setFillColor(sf::Color(255, 255, 255, 255));
            msg = "WAVE CLEARED!";
        }
        // if(colorPos==colors.size()) {
        //     colorPos=0;
        // }
    }

    if (showAnnoucement == false && gameTime.getElapsedTime().asSeconds() > lastActionFrame + 2)
    {
        if (annoucementText->text->getFillColor().a > 0)
        {
            annoucementText->text->setFillColor(sf::Color(255, 255, 255, annoucementText->text->getFillColor().a - 5));
        }
        if (annoucementText->text->getFillColor().a == 0)
        {
            annoucementText->text->setString("");
        }
    }

    crosshair->sprite->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    // health->text->setString(std::to_string(player->health));

    int enemyCount = 0;

    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
        if (entities[i]->hatesPlayer == true)
        {
            enemyCount++;
        }
    }

    for (int i = 0; i < ui.size(); i++)
    {
        ui[i]->update(deltaTime);
    }

    if (enemyCount == 0)
    {
        

        if (spawn == true)
        {
            b1->text->setString("");
            spawn = false;
            wave++;
            waveCounter->text->setString("WAVE " + std::to_string(wave));
            sSpawnWaves();
        }
    }

    scoreCounter->text->setString("SCORE " + std::to_string(score));

    if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 5 && player->mana < 4)
    {
        player->mana++;
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
    }

    if (shake > 0)
    {

        int shakeIntensity;
        if (player->actionTag == "hurt")
        {
            shakeIntensity = 30;
        }
        else
        {
            shakeIntensity = 10;
        }

        view.setCenter(sf::Vector2f(WINDOW_W / 2 + std::rand() % shakeIntensity, WINDOW_H / 2 + std::rand() % shakeIntensity));
        window.setView(view);
        shake -= gameTime.getElapsedTime().asSeconds() - lastActionFrame;
    }
    else
    {
        view.setCenter(sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2));
        window.setView(view);
    }
}

void Scene_Play::sSpawnWaves()
{

    showAnnoucement = true;

    lastActionFrame = gameTime.getElapsedTime().asSeconds();
    if (wave == 1)
    {
        entities.push_back(new Guard);
        entities.push_back(new Guard);
        entities.push_back(new Archer);
    }
    else
    {
        for (int i = 1; i <= wave / i; i++)
        {
            entities.push_back(new Guard);
            entities.push_back(new Warrior);
            entities.push_back(new Archer);
        }
    }
}

void Scene_Play::sSelectBuff()
{

    // incPD == increase DMG 
    // incPH == increase HEALTH
    // incPF == increase FIRERATE

    b1->text->setString("incPD");
}