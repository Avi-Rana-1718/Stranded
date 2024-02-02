class CShape
{
    
public:
    int width;
    int height;
    sf::RectangleShape rect;

    CShape(float w, float h, sf::Color color, sf::Color outline_color, int outline_thickness) : rect(sf::Vector2f(w, h))
    {
        width=w;
        height=h;
        rect.setFillColor(color);
        rect.setOutlineColor(outline_color);
        rect.setOutlineThickness(outline_thickness);
    }
};

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
