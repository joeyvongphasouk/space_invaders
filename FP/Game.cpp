#include "Game.h"

using namespace sf;

// Private Implementations
void Game::initWind()
{
    // Initialize window
    window = new RenderWindow( VideoMode(1000, 1000), "Space Invaders", Style::Close | Style::Titlebar);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(false);

    // Initialize game continue state to be true
    continueGame = true;
}
void Game::initPlayer()
{
    player = new Player();
}
void Game::initTextures()
{
    // Map textures to specific png file from textures folder
    textures["BULLET"] = new sf::Texture();
    textures["BULLET"]->loadFromFile("Textures/bullet3.png");

    textures["ENEMY"] = new sf::Texture();
    textures["ENEMY"]->loadFromFile("Textures/enemy_one.png");
}
void Game::initGUI()
{
    // Load font for GUI
    if(!font.loadFromFile("Fonts/space_invaders.ttf"))
    {
        std::cout << "ERROR: Font failed to load" << std::endl;
    }
    pointText.setFont(font);
    pointText.setCharacterSize(80);
    pointText.setFillColor(sf::Color::White);

    // Here is code that would be implemented if sf::Text gameOver did not crash the executable
    // For more information, look at header file

    // this->gameOver.setFont(font);
    // this->gameOver.setCharacterSize(10);
    // this->gameOver.setFillColor(sf::Color::Red);
    // this->gameOver.setPosition(500 - gameOver.getGlobalBounds().width / 2.f, 500 - gameOver.getGlobalBounds().height / 2.f);
}
void Game::initEnemies()
{
    // Initalize enemies by making new enemy class
    // Class will have sprite and be set according to parameters
    for (int col = 0; col < 10; col++)
    {
        std::vector<Enemy*> temp;
        for (int row = 0; row < 10; row++)
        {
        temp.push_back(new Enemy(40 + (col * 80), 100 + (row * 40), textures["ENEMY"], enSpeed));
        }
        eVect.push_back(temp);
    }
}
void Game::initBackground()
{
    // Load background file
    // Background file has to match the enemy win condition of barrier
    if(!bgTexture.loadFromFile("Textures/background.png"))
    {
        std::cout << "ERROR: Background failed to load" << std::endl;
    }
    background.setTexture(bgTexture);
}
void Game::initXVari()
{
    enSpeed = 40.0f; // Round 1 speed is slow so set movecooldown to 40
    points = 0;
    direction = false;
}

// Public Implementations
Game::Game(/* args */)
{
    // Initialize everything through own functions
    initXVari();
    initWind();
    initTextures();
    initPlayer();
    initEnemies();
    initBackground();
    initGUI();
}
Game::~Game()
{
    // Deallocate pointers to window and player
    delete window;
    delete player;

    // Deallocate all mapped texture files used
    for (auto &textureDelete : textures)
    {
        delete textureDelete.second;
    }

    // Deallocate player bullets
    for (auto *i : bVect)
    {
        delete i;
    }

    // Deallocate enemy bullets
    for (auto *i : enBullVect)
    {
        delete i;
    }

    // Deallocate enemies
    for (auto i : eVect)
    {
        for (auto *j : i)
        {
            delete j;
        }
    }
}

void Game::run()
{
    while (window->isOpen())
    {
        // Still check for window events
        updatePollEvents();

        // If continue game is true, then keep updating game
        if (continueGame)
        {
            update();
        }
        render();
    }
}

void Game::update()
{
    // Update all through their own functions
    updateWin();
    updateInput();
    updateBullet();
    updateEnemy();
    player->update();
    updateCollision();

    updateGUI();
}
void Game::updatePollEvents()
{
    // Check for closed event
    Event windEvent;
    while(window->pollEvent(windEvent))
    {
        switch (windEvent.type)
        {
        case Event::KeyPressed:
            if (windEvent.key.code == Keyboard::Escape) {
                window->close();
            }
            break;
        case Event::Closed:
            window->close();
            break;
        
        default:
            break;
        }
    }
}
void Game::updateInput()
{
    // Check for user input and signal to player sprite

    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
    {
        player->move(-1.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
    {
        player->move(1.f);
    }

    if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && player->canAtt())
    {
        float x = player->getBounds().width / 2.0 + player->getPos().x - 20;
        float y = player->getPos().y;
        bVect.push_back(new Bullet(textures["BULLET"], x, y, -1, 15));
    }

    // DEV MODE IF YOU WANT TO DO COOL THINGS
    // Increase  speed
    if (Keyboard::isKeyPressed(Keyboard::I))
    {
        player->setAttackSpeed(player->getAttackSpeed() - 0.2f);
    }
    // Decrease attack speed
    if (Keyboard::isKeyPressed(Keyboard::O))
    {
        player->setAttackSpeed(player->getAttackSpeed() + 0.2f);
    }
}
void Game::updateBullet()
{
    int counter = 0;
    for (auto *i : bVect)
    {
        i->update();

        // Delete bullet to stop memory leaks
        if(i->getBounds().top + i->getBounds().height < 0.f)
        {
            delete bVect.at(counter);
            bVect.erase(bVect.begin() + counter);

            // Below is code that will print amount of bullets, checks if deleting properly
            // std::cout << "Amount of bullets in bullet vector: " << bVect.size() << std::endl;

        }
        ++counter;
    }

    int counterEn = 0;
    for (auto *i : enBullVect)
    {
        i->update();
        // Delete bullet to stop memory leaks
        if(i->getBounds().top > 1000.f)
        {
            delete enBullVect.at(counterEn);
            enBullVect.erase(enBullVect.begin() + counterEn);

            // Below is code that will print amount of bullets, checks if deleting properly
            // std::cout << "Amount of enbullets in enbullet vector: " << enBullVect.size() << std::endl;

        }
        ++counterEn;
    }


}
void Game::updateEnemy()
{
    bool dirSwitch = false;
    bool removedEnemy = false;
    int probShoot;

    // Iterate through 2d Enemy vector
    for (unsigned int i = 0; i < eVect.size(); i++)
    {
        for (unsigned int j = 0; j < eVect[i].size(); j++)
        {


            // Check if enemy is at edge,
            // if so, toggle flip switch for all enemies
            if (eVect[i][j]->update(direction) != direction)
            {
                dirSwitch = true;
            }

            probShoot = rand() % 10000;
            if (probShoot < 1)
            {
                float x = eVect[i][j]->getBounds().width / 2.0 + eVect[i][j]->getPos().x;
                float y = eVect[i][j]->getPos().y;
                enBullVect.push_back(new Bullet(textures["BULLET"], x, y, 1, 15));
            }


            // Check for every bullet on screen if intersect,
            // if so, then remove both enemy and bullet.
            // Also stop for loop so that it stops checking for more bullets
            for (unsigned int k = 0 ; k < bVect.size() && !removedEnemy; k++)
            {
                if (bVect[k]->getBounds().intersects(eVect[i][j]->getBounds()))
                {
                    delete bVect.at(k);
                    bVect.erase(bVect.begin() + k);

                    delete eVect[i].at(j);
                    eVect[i].erase(eVect[i].begin() + j);
                    removedEnemy = true;

                    points += 100;

                    // Below is a counter that will print to terminal the size of terminals

                    // int counter = 0;
                    // for (int p = 0; p < eVect.size(); p++)
                    // {
                    //     counter += eVect[p].size();
                    // }
                    // std::cout << "Amount of enemies in enemy vector: " << counter << std::endl;
                }
            }
        }
    }

    if (dirSwitch == true)
    {
        direction = !direction;
        for (auto i : eVect){
            for (auto *j : i)
            {
                j->shiftDown();
            }
        }
    }
}
void Game::updateWin()
{
    // Iterate through enemies to see if past border
    int counter = 0;
    for (unsigned int i = 0; i < eVect.size() && continueGame; i++)
    {
        for (unsigned int j = 0; j < eVect[i].size() && continueGame; j++)
        {
            if (eVect[i][j]->getBounds().top >= 800)
            {
            continueGame = false;
            }
            ++counter;
        }
    }

    // Iterate through bullets to see if hit player
    for(unsigned int k = 0 ; k < enBullVect.size(); k++)
    {
        if (enBullVect[k]->getBounds().intersects(player->getBounds()))
        {
            continueGame = false;
            delete enBullVect.at(k);
            enBullVect.erase(enBullVect.begin() + k);
        }
    }
    
    

    // If before conditions false, then continue game and initialize new enemies
    if (continueGame)
    {
        if (counter == 0)
        {
            enSpeed -= 8.0f; // Initialize new enemies with faster speed
            std::cout << "NEXT ROUND: Can you survive this time?" << enSpeed << std::endl;
            initEnemies();

            // load text file for next round
        }
    }
    else
    {
        // If false, then call to gameover screen
    }
}
void Game::updateGUI()
{
    pointText.setString("Points: " + points);
}
void Game::updateCollision()
{
    // Check if player's position is out of bounds
    if (player->getBounds().left < 0.f)
    {
        player->setPosition(0.f, player->getBounds().top);
    }
    if (player->getBounds().left + player->getBounds().width > 1000)
    {
        player->setPosition(1000.f - player->getBounds().width, player->getBounds().top);
    }
}

void Game::renderGUI()
{
    pointText.setString("Points: " + std::to_string(points));
    window->draw(pointText);

    // Problem with gameOver text file, reference header file

    // this->gameOver.setString("Game Over");
}
void Game::renderBG()
{
    window->draw(background);
}
void Game::render()
{
    window->clear();

    // Render all drawn objects
    renderBG();
    player->render(*window);

    // Render all objects in lists
    for (auto *i : bVect)
    {
        i->render(window);
    }
    for (auto i : eVect)
    {
        for (auto *j : i)
        {
            j->render(window);
        }
    }
    for (auto *i : enBullVect)
    {
        i->render(window);
    }

    renderGUI();

    // Here is code that would be implemented if sf::Text gameOver did not crash the executable
    // For more information, look at header file

    // if (!continueGame)
    // {
    //     window->draw(gameOver);
    // }
    window->display();
}