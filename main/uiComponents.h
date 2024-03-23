#include <string>

class Window
{

public:
    sf::Font font;
    sf::Text title;

    float posX;
    float posY;


    CShape *cshape = new CShape(100, 4, sf::Color(112, 128, 144), sf::Color(255, 255, 255), 3);

    Window(sf::Font &font, float posX=0.f, float posY=0.f)
    {


        // select the font
        title.setFont(font); // font is a sf::Font
        title.setString("Hello world");
        title.setCharacterSize(24); // in pixels, not points!
        cshape->circle.setOrigin(0,0);
        title.setPosition(posX+50-24, posY+24);
        cshape->circle.setRotation(45.f);
    }
};
