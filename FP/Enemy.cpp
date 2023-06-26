#include "Enemy.h"

using namespace sf;

// Private Function Implementations
void Enemy::initVari(float startX, float startY, float enMoveSpeed)
{
    // Initialize position of enemy to starting pos
    posX = startX;
    posY = startY;
    speed = 5.0f;

    // Initialize others
    dead = false;
    moveCooldownMax = enMoveSpeed;
    moveCooldown = moveCooldownMax;
}
void Enemy::initSprite(Texture* enemyTexture)
{
    // Initialize sprite and scale down
    enemySprite.setTexture(*enemyTexture);
    enemySprite.scale(0.04f, 0.04f);
}



// Constructors and Destructors
Enemy::Enemy(float startX, float startY, Texture* texture, float enMoveSpeed)
{
    initVari(startX, startY, enMoveSpeed);
    initSprite(texture);
    enemySprite.setPosition(startX, startY);
}
Enemy::~Enemy()
{
    //
}

// Getters and Setters
float const Enemy::getMoveSpeed()
{
    return moveCooldownMax;
}
const Vector2f & Enemy::getPos() const
{
    return enemySprite.getPosition();
}

// Enemy Functions
bool Enemy::update(bool direction)
{
    return updatePosition(direction);
}
bool Enemy::updatePosition(bool direction)
{
    if (moveCooldown >= moveCooldownMax)
    {
        // Direction goes right
        if (direction == false)
        {
            enemySprite.move(speed, 0);
            if (enemySprite.getPosition().x >= 900) // Check if reach end
            {
                direction = true;
            }
        }

        // Direction goes left
        else
        {
            enemySprite.move(-speed, 0);
            if (enemySprite.getPosition().x <= 40) // Check if reach end
            {
                direction = false;
            }
        }
        moveCooldown = 0.f;
    }
    else
    {
        moveCooldown += 1.0f;
    }
    return direction;
}

const FloatRect Enemy::getBounds() const
{
    return enemySprite.getGlobalBounds();
}

void Enemy::shiftDown()
{
    enemySprite.move(0, 40);
}

// Window and Draw functions
void Enemy::render(RenderTarget* target)
{
    target->draw(enemySprite);
}