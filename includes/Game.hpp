/**
 * @file Game.hpp
 * @author Seyitahmet Genç
 * @brief Game class and its function definitions
 * @date 2021-05-13
 *
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "Bullet.hpp"
#include "Constants.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "RenderWindow.hpp"

class Game
{
  public:
    /**
     * @brief Construct a new Game object. it calls init function.
     *
     */
    Game();

    /**
     * @brief Destroy the Game object. it calls destroy function
     *
     */
    ~Game();

    /**
     * @brief process user input in this function. it handles events like
     * SDL_QUIT or keypresses.
     *
     */
    void processInput();

    /**
     * @brief this function runs on every frame and updates our game world as
     *  player movement, enemy movement, bullet movement or collision detection
     * etc.
     *
     */
    void update();

    /**
     * @brief render current frame. this function draws all entities on screen,
     * then calls SDL_RenderPresent for rendering the frame.
     *
     */
    void render();

    /**
     * @brief when game is over, this function prints the user's score to the
     * screen.
     *
     */
    void showGameOver();
    bool getIsRunning() { return this->isRunning; }
    bool getIsPaused() { return this->isPaused; }

  private:
    /**
     * @brief checks if two entities collide. it runs simple rectangular
     * collision because our entities use rectangles (SDL_Rect).
     *
     * @param first first entity to check
     * @param second second entity to check
     * @return true if two entities collide
     * @return false if they don't collide
     */
    bool isCollide(Entity &first, Entity &second);

    /**
     * @brief initialize private variables like isPaused, enemyCount.
     * create our render window and player...
     * briefly it initializes our game components.
     */
    void init();

    /**
     * @brief free the memory allocated by game components.
     *
     */
    void destroy();

    /**
     * @brief render current score on the screen. (top-left)
     *
     */
    void renderScore();

    /**
     * @brief render remaining health on the screen(top-right)
     *
     */
    void renderHealth();

    /**
     * @brief render "Game is paused." text if game is paused
     *
     */
    void renderPaused();

  private:
    bool isRunning;
    bool isPaused;
    RenderWindow *window;
    Player *hus;
    int enemyCount;
    std::vector<Enemy> enemies;
    int maxBullets;
    std::vector<Bullet> bullets;
    int score;
    int health;
    TTF_Font *smallFont;
    TTF_Font *bigFont;
};
