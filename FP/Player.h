#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Player
{
private:
    // Private vari
    sf::Sprite rShip;
    sf::Texture rShipText;

    float speed;
    float attCooldown;
    float attCooldownMax;

    // Private Func
    void initVari();
    void initTexture();
    void initSprite();
public:
    Player(/* args */);
    virtual ~Player();

    // Getters and Setters
    const sf::Vector2f & getPos() const;
    const float getAttackSpeed() const;

    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setAttackSpeed(float newSpeed);

    // Public Functions
    void render(sf::RenderTarget& target);
    void update();
    void updateAttack();

    const sf::FloatRect getBounds() const;

    void move(float direction);
    const bool canAtt();
};

#endif