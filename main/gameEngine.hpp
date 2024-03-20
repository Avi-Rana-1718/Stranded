#include "global.hpp"
#include "scenes/Scenes.hpp"

#include "scenes/Scenes_Play.hpp"

class GameEngine
{

    bool isRunning;
    int totalFrames;

public:
    sf::Event event;

    Scenes *currentScene = NULL;
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

    assets.addTexture("slime/large/move0.png");
    assets.addTexture("slime/large/move1.png");
    assets.addTexture("slime/large/move2.png");
    assets.addTexture("slime/large/hit.png");
    assets.addTexture("slime/large/die.png");

    assets.addTexture("ui/heart.png");
    assets.addTexture("map.png");

    assets.addFont("noto.ttf");

    currentScene = new Scene_Play;
    window.create(sf::VideoMode(WINDOW_W, WINDOW_H), "Dice wizard");
    window.setFramerateLimit(144);
    isRunning = true;
    totalFrames = 0;
}

void GameEngine::run()
{

    while (isRunning)
    {

        sf::Time time = Clock.restart();

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