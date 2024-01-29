
class CShape {
    public:
    sf::CircleShape circle;
    CShape(float r, float edges) : circle(r, edges) {
        circle.setFillColor(sf::Color::Red);
    }
};

