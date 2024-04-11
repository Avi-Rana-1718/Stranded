#include "global.hpp"
#include "particles.hpp"
#include "scenes/Scenes.hpp"

#include "scenes/Scenes_Over.hpp"
#include "scenes/Scenes_Credits.hpp"
#include "scenes/Scenes_Play.hpp"
#include "scenes/Scenes_Menu.hpp"

#include "./entities/ui/button.hpp"

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

    window.create(sf::VideoMode::getDesktopMode(), "Dice wizard", sf::Style::Fullscreen);
    WINDOW_W = window.getSize().x;
    WINDOW_H = window.getSize().y;

    assets.addTexture("player/idle0.png");
    assets.addTexture("player/idle1.png");
    assets.addTexture("player/idle2.png");
    assets.addTexture("player/idle3.png");
    assets.addTexture("player/idle4.png");
    assets.addTexture("player/move-h0.png");
    assets.addTexture("player/move-h1.png");
    assets.addTexture("player/move-h2.png");
    assets.addTexture("player/move-h3.png");

    assets.addTexture("player/hurt.png");
    assets.addTexture("player/die.png");

    assets.addTexture("guard/idle0.png");
    assets.addTexture("guard/idle1.png");
    assets.addTexture("guard/idle2.png");
    assets.addTexture("guard/idle3.png");
    assets.addTexture("guard/idle4.png");

    assets.addTexture("guard/attack0.png");
    assets.addTexture("guard/attack1.png");
    assets.addTexture("guard/attack2.png");
    assets.addTexture("guard/attack3.png");
    assets.addTexture("guard/attack4.png");

    assets.addTexture("guard/die0.png");

    assets.addTexture("warrior/idle0.png");
    assets.addTexture("warrior/idle1.png");
    assets.addTexture("warrior/idle2.png");
    assets.addTexture("warrior/idle3.png");
    assets.addTexture("warrior/idle4.png");

    assets.addTexture("warrior/attack0.png");
    assets.addTexture("warrior/attack1.png");
    assets.addTexture("warrior/attack2.png");
    assets.addTexture("warrior/attack3.png");
    assets.addTexture("warrior/attack4.png");

    assets.addTexture("warrior/hit.png");

    assets.addTexture("warrior/die0.png");

    assets.addTexture("archer/idle0.png");
    assets.addTexture("archer/idle1.png");
    assets.addTexture("archer/idle2.png");
    assets.addTexture("archer/idle3.png");
    assets.addTexture("archer/idle4.png");

    assets.addTexture("archer/move0.png");
    assets.addTexture("archer/move1.png");
    assets.addTexture("archer/move2.png");
    assets.addTexture("archer/move3.png");

    assets.addTexture("archer/attack0.png");
    assets.addTexture("archer/attack1.png");
    assets.addTexture("archer/attack2.png");
    assets.addTexture("archer/attack3.png");
    assets.addTexture("archer/attack4.png");
    assets.addTexture("archer/attack5.png");
    assets.addTexture("archer/attack6.png");

    assets.addTexture("archer/hurt.png");
    assets.addTexture("archer/die.png");

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
    assets.addFont("epilogue.ttf");
    assets.addFont("technicality.ttf");

    assets.addTexture("gun.png");
    assets.addTexture("crosshair.png");

  scenes["menu"] = new Scene_Menu;
    scenes["play"] = new Scene_Play;
    scenes["credits"] = new Scene_Credits;
    scenes["over"] = new Scene_Over;

    currentScene = scenes["play"];
    window.setFramerateLimit(144);
    isRunning = true;
    totalFrames = 0;

    view.setCenter(sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2));
    view.setSize(sf::Vector2f(WINDOW_W, WINDOW_H));
    window.setView(view);
}

void GameEngine::run()
{
    currentScene->init();

    while (isRunning && currentScene != NULL)
    {

        sf::Time time = Clock.restart();
        totalFrames++;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.create(sf::VideoMode::getDesktopMode(), "Dice wizard");
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
        {
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