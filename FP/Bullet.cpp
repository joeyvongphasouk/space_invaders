#include "Bullet.h"

using namespace sf;

Bullet::Bullet(Texture * texture, float posX, float posY, float directY, float speed)
{
    shape.setTexture(*texture);
    shape.scale(1.5f, 1.5f);
    direction = directY;
    if (direction == 1)
    {
        shape.rotate(180);
    }
    shape.setPosition(posX, posY);
    this->speed = speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
    return shape.getGlobalBounds();
}

void Bullet::render(RenderTarget* target)
{
    target->draw(shape);
}

void Bullet::update()
{
    shape.move(0, speed * direction);
}