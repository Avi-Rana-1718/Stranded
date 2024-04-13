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

public:
    sf::Event event;
    sf::Music music;

    AssetManager assets;

    GameEngine();

    // functions
    void run();
};

GameEngine::GameEngine()
{

    window.create(sf::VideoMode::getDesktopMode(), "Stranded", sf::Style::Fullscreen);
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

    assets.addTexture("guard/move0.png");
    assets.addTexture("guard/move1.png");
    assets.addTexture("guard/move2.png");
    assets.addTexture("guard/move3.png");

    assets.addTexture("guard/attack0.png");
    assets.addTexture("guard/attack1.png");
    assets.addTexture("guard/attack2.png");
    assets.addTexture("guard/attack3.png");
    assets.addTexture("guard/attack4.png");

    assets.addTexture("guard/hurt.png");
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

    assets.addTexture("shell/explosion/0.png");

    assets.addTexture("ui/heart.png");
    assets.addTexture("ui/energy.png");

    assets.addTexture("map.png");
    assets.addTexture("ship.png");

    assets.addTexture("ui/inputs/mouse_left.png");
    assets.addTexture("ui/inputs/keyboard_arrows_all.png");

    assets.addFont("epilogue.ttf");
    assets.addFont("technicality.ttf");
    assets.addFont("technicality1.ttf");

    assets.addTexture("gun.png");
    assets.addTexture("crosshair.png");

    assets.addSound("hurt.wav");
    assets.addSound("shot.wav");
    assets.addSound("upgrade.wav");
    assets.addSound("select.wav");


    scenes["menu"] = new Scene_Menu;
    scenes["play"] = new Scene_Play;
    scenes["credits"] = new Scene_Credits;
    scenes["over"] = new Scene_Over;

    currentScene = scenes["menu"];
    window.setFramerateLimit(144);
    isRunning = true;
    totalFrames = 0;

    view.setCenter(sf::Vector2f(WINDOW_W / 2, WINDOW_H / 2));
    view.setSize(sf::Vector2f(WINDOW_W, WINDOW_H));
    window.setView(view);

    if (!music.openFromFile("./assets/dos88.ogg"))
    {
        std::cout << "ASSET: DOS88 NOT FOUND\n";
    }
    music.setVolume(50);
    music.setLoop(true);
    music.play();
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