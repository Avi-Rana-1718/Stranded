#include "../entities/Player.hpp"
#include "../entities/Guard.hpp"
#include "../entities/Warrior.hpp"
#include "../entities/Archer.hpp"

#include "../entities/Gun.hpp"
#include "../entities/bg/map.hpp"
#include "../entities/ui/heart.hpp"
#include "../entities/ui/energy.hpp"
#include "../entities/ui/crosshair.hpp"
#pragma once

class Scene_Play : public Scenes
{
public:
    Entity *player, *crosshair, *par;

    std::vector<Entity *> hearts;
    Entity* energy;

    // ui elements
    Entity *waveCounter;
    Entity *scoreCounter;
    Entity *annoucementText;

    Entity *b1, *b2, *b3;
    Entity *u1, *u2;
    Entity *btnBg;
    Entity *bgTitle;
    std::string bgStr = "Select Powerup";

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
    // window.setMouseCursorVisible(false);

    
    // crosshair
    crosshair = new Crosshair;
    ui.push_back(crosshair);

    // entities
    player = new Player;
    entities.push_back(player);
    entities.push_back(new Gun(player));


    wave = 0;
    score = 0;

    lastActionFrame = gameTime.getElapsedTime().asSeconds();

    showAnnoucement = false;

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

    for (int i = 0; i < 5; i++)
    {
        Entity *temp = new HP;
        int intend = (i == 0) ? 0 : 20;
        temp->sprite->move((temp->sprite->getGlobalBounds().getSize().x * temp->scale * i) - intend * i, 0);
        hearts.push_back(temp);
        ui.push_back(temp);
    }

    // ui.push_back(new Energy);

    par = new Entity;
    par->particles = new ParticleSystem(WINDOW_W, WINDOW_W);
    ui.push_back(par);

    // ui - powerup btns

    btnBg = new Entity;
    btnBg->shape = new sf::RectangleShape(sf::Vector2f(WINDOW_W + 200, WINDOW_H / 2.5));
    btnBg->shape->setPosition(-100, WINDOW_H / 3);
    btnBg->shape->setFillColor(sf::Color(40, 40, 40));
    btnBg->shape->setRotation(-2);
    ui.push_back(btnBg);

    bgTitle = new Entity;
    bgTitle->text = new sf::Text;
    bgTitle->text->setFont(m_fonts["epilogue.ttf"]);
    bgTitle->text->setString("Select powerup");
    bgTitle->text->setOutlineColor(sf::Color(40, 40, 40));
    bgTitle->text->setOutlineThickness(1.5);
    bgTitle->text->setCharacterSize(50);
    bgTitle->text->setOrigin(bgTitle->text->getGlobalBounds().getSize().x / 2, bgTitle->text->getGlobalBounds().getSize().y / 2);
    bgTitle->text->setPosition(WINDOW_W / 2, btnBg->shape->getGlobalBounds().getPosition().y + 100);
    bgTitle->text->setFillColor(sf::Color::White);
    ui.push_back(bgTitle);

    b1 = new Button("", "");
    b1->text->setPosition(WINDOW_W * 1 / 3 - 400, WINDOW_H / 2);
    ui.push_back(b1);

    b2 = new Button("", "");
    b2->text->setPosition(WINDOW_W * 2 / 3 - 400, WINDOW_H / 2);
    ui.push_back(b2);

    b3 = new Button("", "");
    b3->text->setPosition(WINDOW_W * 3 / 3 - 400, WINDOW_H / 2);
    ui.push_back(b3);

    // mouse & keyboard

    u2 = new Entity;
    u2->scale = 0.8;
    u2->sprite = new CSprite(m_textures["ui/inputs/keyboard_arrows_all.png"]);
    u2->sprite->setPosition(10, WINDOW_H / 2 - 100);
    u2->text = new sf::Text;
    u2->text->setFont(m_fonts["technicality.ttf"]);
    u2->text->setString("WASD to move!");
    u2->text->setOutlineColor(sf::Color(40, 40, 40));
    u2->text->setOutlineThickness(1.5);
    u2->text->setCharacterSize(20);
    u2->text->setPosition(10 + u2->sprite->getGlobalBounds().getSize().x, u2->sprite->getPosition().y + ((m_textures["ui/inputs/keyboard_arrows_all.png"].getSize().y / 2) * 0.8));
    u2->text->setFillColor(sf::Color::White);
    ui.push_back(u2);

    u1 = new Entity;
    u1->sprite = new CSprite(m_textures["ui/inputs/mouse_left.png"]);
    u1->sprite->setPosition(u2->sprite->getGlobalBounds().getPosition().x / 2 + 10, u2->sprite->getPosition().y + u2->sprite->getGlobalBounds().getSize().y - 25);
    u1->scale = 0.6;
    u1->text = new sf::Text;
    u1->text->setFont(m_fonts["technicality.ttf"]);
    u1->text->setString("Left click to shoot!");
    u1->text->setOutlineColor(sf::Color(40, 40, 40));
    u1->text->setOutlineThickness(1.5);
    u1->text->setCharacterSize(20);
    u1->text->setPosition(10 + u2->sprite->getGlobalBounds().getSize().x, u1->sprite->getPosition().y + ((m_textures["ui/inputs/mouse_left.png"].getSize().y / 2) * 0.6));
    u1->text->setFillColor(sf::Color::White);
    ui.push_back(u1);

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
    }

void Scene_Play::update()
{

    par->particles->update(-10, -10);

    // change crosshair position
    // crosshair->sprite->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

    // change/set score
    scoreCounter->text->setString("SCORE " + std::to_string(score));

    // health
    if (player->health == 5)
    {
        for (int i = 0; i < 5; i++)
        {
            hearts[i]->sprite->setColor(sf::Color(255, 255, 255));
        }
    }
    else if (player->health == 4)
    {
        for (int i = 0; i < 4; i++)
        {
            hearts[i]->sprite->setColor(sf::Color(255, 255, 255));
        }

        hearts[4]->sprite->setColor(sf::Color(255, 255, 255, 128));
    }
    else if (player->health == 3)
    {
        for (int i = 0; i < 3; i++)
        {
            hearts[i]->sprite->setColor(sf::Color(255, 255, 255));
        }

        hearts[3]->sprite->setColor(sf::Color(255, 255, 255, 128));
        hearts[4]->sprite->setColor(sf::Color(255, 255, 255, 128));
    }
    else if (player->health == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            hearts[i]->sprite->setColor(sf::Color(255, 255, 255));
        }

        hearts[2]->sprite->setColor(sf::Color(255, 255, 255, 128));
        hearts[3]->sprite->setColor(sf::Color(255, 255, 255, 128));
        hearts[4]->sprite->setColor(sf::Color(255, 255, 255, 128));
    }
    else if (player->health == 1)
    {
        for (int i = 0; i < 1; i++)
        {
            hearts[i]->sprite->setColor(sf::Color(255, 255, 255));
        }

        hearts[1]->sprite->setColor(sf::Color(255, 255, 255, 128));
        hearts[2]->sprite->setColor(sf::Color(255, 255, 255, 128));
        hearts[3]->sprite->setColor(sf::Color(255, 255, 255, 128));
        hearts[4]->sprite->setColor(sf::Color(255, 255, 255, 128));
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            hearts[i]->sprite->setColor(sf::Color(255, 255, 255, 128));
        }
    }

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

        if (wave % 5 != 0 || wave < 5)
        {
            spawn = true;
        }
        else
        {
            sSelectBuff();
            btnBg->shape->setFillColor(sf::Color(40, 40, 40));
            bgTitle->text->setString(bgStr);
        }

        if (spawn == true)
        {
            b1->text->setString("");
            b2->text->setString("");
            b3->text->setString("");
            btnBg->shape->setFillColor(sf::Color(40, 40, 40, 0));
            bgTitle->text->setString("");

            spawn = false;
            wave++;
            waveCounter->text->setString("WAVE " + std::to_string(wave));
            sSpawnWaves();
        }

        // delete control tut
        if (wave == 2)
        {
            for (int i = 0; i < ui.size(); i++)
            {
                if (ui[i] == u1)
                {
                    delete u1;
                    ui.erase(ui.begin() + i);
                }
            }
            for (int i = 0; i < ui.size(); i++)
            {
                if (ui[i] == u2)
                {
                    delete u2;
                    ui.erase(ui.begin() + i);
                }
            }
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

    // game over
        if(player->actionTag=="die") {
        currentScene=scenes["over"];
        currentScene->init();
    }

}

void Scene_Play::sSpawnWaves()
{

    if (wave != 1)
    {
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
        for (int i = 1; i <= wave / i + 1 ; i++)
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

    if (b1->text->getString() == "")
    {
        b1->text->setString("incPD");
    }

    if (b2->text->getString() == "")
    {
        b2->text->setString("incPH");
    }

    if (b3->text->getString() == "")
    {
        b3->text->setString("incPF");
    }
}