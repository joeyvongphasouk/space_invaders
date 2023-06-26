/* CSCI 261: Final Project
 *
 * Author: Joey Vongphasouk
 * Resources used: https://www.youtube.com/watch?v=BySDfVNljG8&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&ab_channel=SurajSharma
 *                 Introductory to Game Design using SFML really helped with overall
 *                 bearings and intial code starting. It had also helped with how to
 *                 structure a game using classes such as the game class and how to use
 *                 object-oriented-programming.
 * 
 *                 https://freeinvaders.org/
 *                 Website had helped me understand what as needed in the general Space
 *                 Invaders game by displaying a properly functioning game. This game had
 *                 helped guide me through the behaviors of the player, enemy, and bullet.
 *                 Once understood, I was able to implement it into the game itself    
 * 
 * The final project's aim was to fully develop a program that can run the classic game
 * Space Invaders. The game works by using SFML to display a playable game onto the desktop.
 * The user is able to control the rocket ship on the bottom using wasd or arrow keys. The
 * goal of the game is to destroy aliens that spawn intermittenly. The game is lost when the
 * player is hit by a missile from the aliens or the aliens have reached Earth.
 */

#include "Game.h"
#include <ctime>
#include <cstdlib>

int main() {

    // Init random (rand bullets from enemy)
    srand( time(0) );
    rand();

    // Run game
    Game game;
    game.run();

    return 0;
}