#pragma once
class GameEngine;
sf::RenderWindow window;
sf::Clock Clock;
sf::Clock gameTime;

int WINDOW_W=1800;
int WINDOW_H=720;

#include "entities/_Entity.hpp"

std::vector<Entity *> entities;
std::vector<Entity *> ui;
