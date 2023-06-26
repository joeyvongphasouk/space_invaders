#ifndef BULLET_H
#define BULELT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:
    sf::Sprite shape;

    float direction;
    float speed;

public:
    Bullet(sf::Texture* texture, float posX, float posY, float directY, float speed);
    ~Bullet();

    const sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget* target);
};

#endif