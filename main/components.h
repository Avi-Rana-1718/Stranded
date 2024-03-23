class CTransform
{
public:
    float speedX, speedY;

    CTransform()
    {
        speedX = 1.0;
        speedY = 1.0;
    }

    CTransform(float sx, float sy)
    {
        speedX = sx;
        speedY = sy;
    }
};

class CSprite : public sf::Sprite
{
public:

    CSprite(sf::Texture &texture)
    {
        setTexture(texture);
        setOrigin(0, 0);
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

class CProjectile {
public:
    int health;
    int lifespan;

    CProjectile(int h, int l) {
        health=h;
        lifespan=l;
    }
};