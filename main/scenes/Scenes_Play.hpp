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

    Entity *b1, *b2, *b3;

    // announcementConfig
    bool showAnnoucement;
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

    showAnnoucement=false;

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

    annoucementText = new Entity;
    annoucementText->text = new sf::Text;
    annoucementText->text->setFont(m_fonts["technicality.ttf"]);
    annoucementText->text->setString("Wave cleared");
    annoucementText->text->setOutlineColor(sf::Color(40, 40, 40));
    annoucementText->text->setOutlineThickness(1.5);
    annoucementText->text->setCharacterSize(50);
    annoucementText->text->setOrigin(annoucementText->text->getGlobalBounds().getSize().x / 2, annoucementText->text->getGlobalBounds().getSize().y / 2);
    annoucementText->text->setPosition(WINDOW_W / 2, 50);
    annoucementText->text->setFillColor(sf::Color::White);
    annoucementText->text->setString("");
    ui.push_back(annoucementText);

    Entity *temp = new HP;
    ui.push_back(temp);

    crosshair = new Crosshair;
    ui.push_back(crosshair);

    par = new Entity;
    par->particles = new ParticleSystem(WINDOW_W, WINDOW_W);
    ui.push_back(par);

    // ui - powerup btns
    b1 = new Button("", "");
    b1->text->setPosition(WINDOW_W*1/3-150, WINDOW_H/2);
    ui.push_back(b1);

    b2 = new Button("", "");
    b2->text->setPosition(WINDOW_W*2/3-150, WINDOW_H/2);
    ui.push_back(b2);

    b3 = new Button("", "");
    b3->text->setPosition(WINDOW_W*3/3-150, WINDOW_H/2);
    ui.push_back(b3);

    // entities
    player = new Player;
    entities.push_back(player);
    entities.push_back(new Gun(player));


    // background
    bg = new Background;
    background.push_back(bg);
}

void Scene_Play::run(float time)
{
    deltaTime = time;

    update();
    sRender();
    sEntityUpdate();

    par->particles->update(-100, -100);
}

void Scene_Play::update()
{

    // change crosshair position
    crosshair->sprite->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

    // change/set score
    scoreCounter->text->setString("SCORE " + std::to_string(score));

    // health->text->setString(std::to_string(player->health));

    // annoucementLogic
    if (gameTime.getElapsedTime().asSeconds() > lastActionFrame + 0.1 && showAnnoucement)
    {
        annoucementText->text->setFillColor(sf::Color(255, 255, 255, 255));
        annoucementText->text->setString(annoucementText->text->getString() + msg.front());
        annoucementText->text->setOrigin(annoucementText->text->getGlobalBounds().getSize().x / 2, annoucementText->text->getGlobalBounds().getSize().y / 2);
        lastActionFrame = gameTime.getElapsedTime().asSeconds();
        msg.erase(msg.begin());
        if (msg.empty())
        {
            showAnnoucement = false;
            annoucementText->text->setFillColor(sf::Color(255, 255, 255, 255));
            msg = "WAVE CLEARED!";
        }
    }

    // announcementLogic hide
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

    //
    int enemyCount = 0;

    // update entities
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
        if (entities[i]->hatesPlayer == true)
        {
            enemyCount++;
        }
    }

    // update ui
    for (int i = 0; i < ui.size(); i++)
    {
        ui[i]->update(deltaTime);
    }

    // new wave spawn checker
    if (enemyCount == 0)
    {

        if(wave%5!=0 || wave<5) {
            spawn=true;
        } else {
            sSelectBuff();
        }

        if (spawn == true)
        {
            b1->text->setString("");
            b2->text->setString("");
            b3->text->setString("");
            spawn = false;
            wave++;
            waveCounter->text->setString("WAVE " + std::to_string(wave));
            sSpawnWaves();
        }
    }

    // screen shake
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

    if(wave!=1) {
        showAnnoucement = true;
    }

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

    if(b1->text->getString()=="") {
    b1->text->setString("incPD");
    }

    if(b2->text->getString()=="") {
    b2->text->setString("incPH");
    }

    if(b3->text->getString()=="") {
        b3->text->setString("incPF");
    }
}