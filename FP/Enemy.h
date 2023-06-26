#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Enemy
{
private:
    // Position of enemy
    float posX;
    float posY;
    float speed;

    // Other enemy variables
    int points;
    bool dead;

    float moveCooldown;
    float moveCooldownMax;

    // Enemy shape and texture
    sf::Sprite enemySprite;

    // Initialize functions
    void initVari(float startX, float startY, float enSpeed);
    void initSprite(sf::Texture* texture);


public:
    Enemy(float startX, float startY, sf::Texture* texture, float enSpeed);
    ~Enemy();

    // Getters and Setters
    float const getMoveSpeed();
    const sf::Vector2f & getPos() const;

    // Enemy Functions
    bool update(bool direction);
    bool updatePosition(bool direction);
    const sf::FloatRect getBounds() const;

    void shiftDown();

    // Window and Draw functions
    void render(sf::RenderTarget* target);

};

#endif