#include <string>

class Window  {
    sf::Font font;
    public:
    
    sf::CircleShape titleRec(100,0, 4.0);

    Window(sf::Font font) {

      sf::Text title;

    // select the font
    title.setFont(font); // font is a sf::Font
    title.setString("100");
    title.setCharacterSize(24); // in pixels, not points!
    title.setPosition(50, 50);
    }
    
    
};