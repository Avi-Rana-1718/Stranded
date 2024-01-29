class controllable {
public:

void move(entity& obj) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
{
    obj.setPosition(obj.getPosition().x-10, obj.getPosition().y);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
{
    pad.setPosition(obj.getPosition().x+10, obj.getPosition().y);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
{
    pad.setPosition(obj.getPosition().x, obj.getPosition().y+10);
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
{
    pad.setPosition(obj.getPosition().x, obj.getPosition().y+10);
}


}


}
    