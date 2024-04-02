#include "global.hpp"
#include "particles.hpp"
#include "scenes/Scenes.hpp"

#include "scenes/Scenes_Play.hpp"
#include "scenes/Scenes_Menu.hpp"


class GameEngine
{

    bool isRunning;

public:
    sf::Event event;
    
    AssetManager assets;

    GameEngine();

    // functions
    void run();
};

GameEngine::GameEngine()
{

    assets.addTexture("blueWizard/idle0.png");
    assets.addTexture("blueWizard/idle1.png");
    assets.addTexture("blueWizard/idle2.png");
    assets.addTexture("blueWizard/idle3.png");
    assets.addTexture("blueWizard/move0.png");
    assets.addTexture("blueWizard/move1.png");
    assets.addTexture("blueWizard/attack0.png");
    assets.addTexture("blueWizard/attack1.png");
    assets.addTexture("blueWizard/attack2.png");
    assets.addTexture("blueWizard/attack3.png");
    assets.addTexture("blueWizard/hurt0.png");
    assets.addTexture("blueWizard/die.png");

    assets.addTexture("blueSkeletonWizard/idle0.png");
    assets.addTexture("blueSkeletonWizard/idle1.png");
    assets.addTexture("blueSkeletonWizard/idle2.png");
    assets.addTexture("blueSkeletonWizard/idle3.png");
    assets.addTexture("blueSkeletonWizard/attack0.png");
    assets.addTexture("blueSkeletonWizard/attack1.png");
    assets.addTexture("blueSkeletonWizard/attack2.png");
    assets.addTexture("blueSkeletonWizard/attack3.png");
    assets.addTexture("blueSkeletonWizard/attack4.png");
    assets.addTexture("blueSkeletonWizard/attack5.png");
    assets.addTexture("blueSkeletonWizard/hit.png");
    assets.addTexture("blueSkeletonWizard/die.png");

    assets.addTexture("redSkeletonWizard/idle0.png");
    assets.addTexture("redSkeletonWizard/idle1.png");
    assets.addTexture("redSkeletonWizard/idle2.png");
    assets.addTexture("redSkeletonWizard/idle3.png");
    assets.addTexture("redSkeletonWizard/attack0.png");
    assets.addTexture("redSkeletonWizard/attack1.png");
    assets.addTexture("redSkeletonWizard/attack2.png");
    assets.addTexture("redSkeletonWizard/attack3.png");
    assets.addTexture("redSkeletonWizard/attack4.png");
    assets.addTexture("redSkeletonWizard/attack5.png");
    assets.addTexture("redSkeletonWizard/hit.png");
    assets.addTexture("redSkeletonWizard/die.png");


    assets.addTexture("spells/explosion/0.png");
    assets.addTexture("spells/explosion/1.png");
    assets.addTexture("spells/explosion/2.png");
    assets.addTexture("spells/explosion/3.png");
    assets.addTexture("spells/explosion/4.png");
    assets.addTexture("spells/explosion/5.png");
    assets.addTexture("spells/explosion/6.png");
    assets.addTexture("spells/explosion/7.png");
    assets.addTexture("spells/explosion/8.png");
    assets.addTexture("spells/explosion/9.png");
    assets.addTexture("spells/explosion/10.png");

    assets.addTexture("slime/blue/move0.png");
    assets.addTexture("slime/blue/move1.png");
    assets.addTexture("slime/blue/move2.png");
    assets.addTexture("slime/blue/hit.png");
    assets.addTexture("slime/blue/die.png");

    assets.addTexture("slime/green/move0.png");
    assets.addTexture("slime/green/move1.png");
    assets.addTexture("slime/green/move2.png");
    assets.addTexture("slime/green/hit.png");
    assets.addTexture("slime/green/die.png");

    assets.addTexture("slime/lime/move0.png");
    assets.addTexture("slime/lime/move1.png");
    assets.addTexture("slime/lime/move2.png");
    assets.addTexture("slime/lime/hit.png");
    assets.addTexture("slime/lime/die.png");

    assets.addTexture("interactables/bronzeVase/idle.png");
    assets.addTexture("interactables/bronzeVase/hit.png");

    assets.addTexture("ui/hp.png");
    assets.addTexture("ui/mp.png");

    assets.addTexture("ui/heart.png");
    assets.addTexture("ui/empty_heart.png");
    
    assets.addTexture("ui/mana.png");
    assets.addTexture("ui/empty_mana.png");

    assets.addTexture("map.png");
    assets.addTexture("ui/bar_blue_mid.png");

    assets.addFont("noto.ttf");
    assets.addFont("singleday.ttf");

    currentScene = new Scene_Menu;
    window.create(sf::VideoMode::getDesktopMode(), "Dice wizard", sf::Style::Fullscreen);
    WINDOW_W = window.getSize().x;
    WINDOW_H = window.getSize().y;
    window.setFramerateLimit(144);
    isRunning = true;
    totalFrames = 0;

    view.setCenter(sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2));
    view.setSize(sf::Vector2f(WINDOW_W, WINDOW_H));
    window.setView(view);
}

void GameEngine::run()
{

    while (isRunning)
    {

        sf::Time time = Clock.restart();
        totalFrames++;


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.create(sf::VideoMode::getDesktopMode(), "Dice wizard");
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) {
            window.create(sf::VideoMode::getDesktopMode(), "Dice wizard", sf::Style::Fullscreen);
        }

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                isRunning = false;
                window.close();
            }
        }

        currentScene->run(time.asSeconds());
    }
}