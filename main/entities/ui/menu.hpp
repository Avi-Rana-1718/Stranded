#include "../_Entity.hpp"
#include "../../scenes/Scenes.hpp"
#pragma once

class Menu : public Entity {

public:
Entity* main;
Entity* btn;

int lines;
bool movable;

Menu(std::string label, std::string main, int l, int x, int y, bool move);

//
void update(float time);
void move();
};

Menu::Menu(std::string label, std::string t,  int l=1, int x=WINDOW_W/2, int y=WINDOW_H/2, bool move=false) {

    btn = new Button("Exit", "close");
    btn->text->setCharacterSize(25);

    main = new Entity;
    main->text = new sf::Text;
    main->text->setCharacterSize(35);
    main->text->setFillColor(sf::Color(204,204,0));
    main->text->setFont(m_fonts["epilogue.ttf"]);
    main->text->setString(t);

    lines=l;
    movable=false;

    std::cout<<"a";

    text = new sf::Text;
    text->setCharacterSize(25);
    text->setFillColor(sf::Color::White);
    text->setFont(m_fonts["epilogue.ttf"]);
    text->setString(label);

    main->shape = new sf::RectangleShape(sf::Vector2f(text->getGlobalBounds().getSize().x + 100, text->getGlobalBounds().getSize().y + btn->text->getGlobalBounds().getSize().y+100));
    main->shape->setFillColor(sf::Color(40, 60, 80));
    main->shape->setOrigin(main->shape->getGlobalBounds().getSize().x/2, main->shape->getGlobalBounds().getSize().y/2);
    main->shape->setOutlineColor(sf::Color(255,255,102));
    main->shape->setOutlineThickness(1);
    main->shape->setPosition(x, y);
    ui.push_back(main);

    ui.push_back(btn);

}

void Menu::update(float time) {
    main->text->setPosition(main->shape->getPosition().x - main->shape->getGlobalBounds().getSize().x/2 + main->shape->getOutlineThickness()*7, main->shape->getPosition().y - main->shape->getGlobalBounds().getSize().y/2 + main->shape->getOutlineThickness()*7);
    text->setPosition(main->shape->getPosition().x - main->shape->getGlobalBounds().getSize().x/2 + main->shape->getOutlineThickness()*7, main->shape->getPosition().y - main->shape->getGlobalBounds().getSize().y/2 + main->shape->getOutlineThickness()*7 + main->text->getGlobalBounds().getSize().y + 20);
    btn->text->setPosition(main->shape->getPosition().x - main->shape->getGlobalBounds().getSize().x/2 + main->shape->getOutlineThickness()*7, main->shape->getPosition().y - main->shape->getGlobalBounds().getSize().y/2 + main->shape->getOutlineThickness()*7 + main->text->getGlobalBounds().getSize().y + 20 + text->getGlobalBounds().getSize().y + 20);
    move();
}

void Menu::move() {
    if(movable && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        main->shape->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }
}