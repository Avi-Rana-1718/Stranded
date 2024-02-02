class CShape
{
    
public:
    int radius;
    sf::CircleShape circle;

    CShape(float r, float edges, sf::Color color, sf::Color outline_color, int outline_thickness) : circle(r, edges)
    {

        radius = r;
        circle.setFillColor(color);
        circle.setOutlineColor(outline_color);
        circle.setOutlineThickness(outline_thickness);
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
