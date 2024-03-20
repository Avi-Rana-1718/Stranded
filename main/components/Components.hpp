#pragma once

class CTransform
{
    // Entity speed (X * Y)
public:
    float speedX = 0;
    float speedY = 0;

    CTransform(float x, float y);
};

CTransform::CTransform(float x, float y)
{
    speedX = x;
    speedY = y;
}

//

class CSprite : public sf::Sprite
{

public:
    CSprite(sf::Texture &texture);
};

CSprite::CSprite(sf::Texture &texture)
{
    setTexture(texture);
}

//