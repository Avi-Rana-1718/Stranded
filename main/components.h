class CTransform
{
public:
    float posX, posY;
    float speedX, speedY;
    float angle; // angle refers to the rotation of the entity aka the way it is facing

    CTransform()
    {
        posX = 100.0;
        posY = 100.0;
        speedX = 1.0;
        speedY = 1.0;
        angle = 1.0;
    }

    CTransform(float px, float py, float sx, float sy, float a)
    {
        posX = px;
        posY = py;
        speedX = sx;
        speedY = sy;
        angle = a;
    }
};

class CSprite
{
public:
    sf::Sprite sprite;
    CSprite(sf::Texture &texture)
    {
        sprite.setTexture(texture);
        sprite.setOrigin(0, 0);
        sprite.setScale(sf::Vector2f(3.f, 3.f));
    }
};

class CTexture
{
public:
    sf::Texture texture;

    void set(std::string img_path)
    {
        if (!texture.loadFromFile("assets/sprite/" + img_path))
        {
            std::cout << img_path << "not found";
        }
    }
};

class CText
{
public:
    sf::Text text;

    CText(sf::Font& font, std::string str)
    {
        text.setFont(font); // font is a sf::Font
        text.setString(str);
        text.setCharacterSize(24); // in pixels, not points!
        text.setFillColor(sf::Color::White);
    }
};