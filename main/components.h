class CShape
{
public:
    sf::CircleShape circle;
    CShape(float r, float edges) : circle(r, edges)
    {
        circle.setFillColor(sf::Color::Red);
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

class CInput
{
public:
    int id;
    CInput()
    {
        id = 0;
    }
};