#include "Player.h"

using namespace sf;

void Player::initVari()
{
    // Initialize variables to use for the player
    speed = 10.f;
    attCooldownMax = 10.f;

    // Initialize to be full so can shoot right away
    attCooldown = attCooldownMax;
}
void Player::initSprite()
{
    // Initialize the sprite and scale down
    rShip.setTexture(rShipText);
    rShip.scale(0.1f, 0.1f);
}
void Player::initTexture()
{
    // Load from texture resources folder
    if (!rShipText.loadFromFile("Textures/rocket_ship.png")) 
    {
        std::cout << "ERROR: Player texture failed to load" << std::endl;
    }
}

const sf::Vector2f& Player::getPos() const
{
    return rShip.getPosition();
}
const float Player::getAttackSpeed() const
{
    return attCooldownMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
    rShip.setPosition(pos);
}
void Player::setPosition(const float x, const float y)
{
    rShip.setPosition(x, y);
}
void Player::setAttackSpeed(float newSpeed)
{
    attCooldownMax = newSpeed;
}

Player::Player()
{
    // Initialize all things to make player
    initTexture();
    initSprite();
    initVari();

    // Set position of player to start at 
    rShip.setPosition(450, 900);
}
Player::~Player()
{
    // Nothing to destruct on Player
}

void Player::render(RenderTarget& target)
{
    target.draw(rShip);
}
void Player::update()
{
    updateAttack();
}
void Player::updateAttack()
{
    // Update attack cooldown. If attack cooldown is lower than max, then add 1
    if (attCooldown < attCooldownMax)
    {
        attCooldown += 1.f;
    }
}

void Player::move(float direction)
{
    rShip.move(direction * speed, 0);
}

const FloatRect Player::getBounds() const 
{
    return rShip.getGlobalBounds();
}

const bool Player::canAtt()
{
    // Check if cooldown has been reached, if so, then reset attack cooldown
    if (attCooldown >= attCooldownMax)
    {
        attCooldown = 0.f;
        return true;
    }
    return false;
}