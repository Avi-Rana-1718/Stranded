#pragma once
class GameEngine;
sf::RenderWindow window;
sf::View view;
sf::Clock Clock;
sf::Clock gameTime;

int totalFrames;
int shake;
int score=0;

int WINDOW_W=1800;
int WINDOW_H=720;

#include "entities/_Entity.hpp"

Entity* bg=NULL;

std::vector<Entity *> entities;
std::vector<Entity *> ui;

#include "scenes/Scenes.hpp"

Scenes *currentScene = NULL;