#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <map>
#include <vector>
#include <string>

class Game
{
private:
// Private Variables
    // Window
    sf::RenderWindow* window;

    // Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bVect;
    std::vector<Bullet*> enBullVect;
    
        // GUI
    sf::Font font;
    sf::Text pointText;

    /*
        ------------------- MASSIVE BUG -------------------
        When trying to initialize the gameOver text, the program
        is able to compile, however the executable cannot run.
        Therefore, the gameOver text screen will not be used.
    */

    // sf::Text gameOver;


        // Background
    sf::Sprite background;
    sf::Texture bgTexture;

    bool continueGame;

    // Player
    Player* player;
    unsigned int points;

    // Enemy
    std::vector<std::vector<Enemy*>> eVect;
    bool direction;
    float enSpeed;

// Private Functions
    void initWind();
    void initTextures();
    void initPlayer();
    void initGUI();
    void initBackground();
    void initXVari();
    void initEnemies();

public:
    // Constructors and Destructors
    Game(/* args */);
    virtual ~Game();

    // Getters and Setters

    // Public Functions
    void run();

    void update();
    void updatePollEvents();
    void updateInput();
    void updateBullet();
    void updateEnemy();
    void updateWin();
    void updateGUI();
    void updateCollision();

    void renderGUI();
    void renderBG();
    void render();
};

#endif