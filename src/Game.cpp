#include "Game.hpp"

#include <ctime>
#include <iostream>
#include <string>

Game::Game() { init(); }

void Game::init()
{
    std::srand(std::time(nullptr));
    isRunning = true;
    isPaused = false;
    score = 0;
    health = 10;

    window = new RenderWindow(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    smallFont = TTF_OpenFont("res/fonts/arial.ttf", 20);
    bigFont = TTF_OpenFont("res/fonts/arial.ttf", 40);

    SDL_Texture *player = window->loadTexture("res/img/hus.png");
    hus =
        new Player(SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT - 128, 64, 128, player);

    enemyCount = 31;
    SDL_Texture *enemy = window->loadTexture("res/img/js.png");
    for (int i = 0; i < enemyCount; i++)
    {
        int xpos = std::rand() % (SCREEN_WIDTH - 32);
        int ypos = std::rand() % 100 - (500);
        enemies.push_back(Enemy(xpos, ypos, 32, 32, enemy));
    }

    maxBullets = 31;
    SDL_Texture *bullet = window->loadTexture("res/img/c.png");
    for (int i = 0; i < maxBullets; i++)
    {
        bullets.push_back(Bullet(0, 0, 32, 32, bullet));
    }
}

void Game::processInput()
{
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (!isPaused)
    {
        if (keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_RIGHT])
        {
            hus->setDirection(0);
        }
        else if (keys[SDL_SCANCODE_LEFT])
        {
            hus->setDirection(-1);
        }
        else if (keys[SDL_SCANCODE_RIGHT])
        {
            hus->setDirection(1);
        }
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEMOTION)
            break;
        if (event.type == SDL_QUIT)
            isRunning = false;
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_p:
                isPaused = !isPaused;
                break;
            }
            if (!isPaused)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    for (Bullet &bullet : bullets)
                    {
                        if (!bullet.getIsFired())
                        {
                            bullet.fire(
                                hus->getXPosition() + bullet.getWidth() / 2,
                                hus->getYPosition() - bullet.getHeight());
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void Game::update()
{
    hus->update();

    for (Enemy &enemy : enemies)
    {
        enemy.update();
        if (enemy.getYPosition() > SCREEN_HEIGHT - hus->getHeight())
        {
            health--;
            enemy.die();
        }
    }

    for (Bullet &bullet : bullets)
    {
        bullet.update();
        if (bullet.getIsFired())
        {
            for (Enemy &enemy : enemies)
            {
                if (isCollide(bullet, enemy))
                {
                    bullet.setIsFired(false);
                    enemy.die();
                    score++;
                }
            }
        }
    }

    if (health <= 0)
    {
        isRunning = false;
    }
}

void Game::render()
{
    window->clear();
    window->render(*hus);
    for (Enemy &enemy : enemies)
    {
        window->render(enemy);
    }
    for (Bullet &bullet : bullets)
    {
        if (bullet.getIsFired())
            window->render(bullet);
    }
    renderScore();
    renderHealth();
    if (isPaused)
    {
        renderPaused();
    }
    window->display();
}

void Game::renderScore()
{
    std::string s = "score: " + std::to_string(score);
    SDL_Surface *text_surface = TTF_RenderText_Shaded(
        smallFont, s.c_str(), {0, 0, 0, 255}, {255, 255, 255, 255});
    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(window->getRenderer(), text_surface);

    SDL_Rect scoreRect;
    scoreRect.x = 0;
    scoreRect.y = 0;
    scoreRect.w = text_surface->w;
    scoreRect.h = text_surface->h;

    SDL_FreeSurface(text_surface);

    SDL_RenderCopy(window->getRenderer(), text_texture, NULL, &scoreRect);
}

void Game::renderHealth()
{
    std::string s = "remaining health: " + std::to_string(health);
    SDL_Surface *text_surface = TTF_RenderText_Shaded(
        smallFont, s.c_str(), {0, 0, 0, 255}, {255, 255, 255, 255});
    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(window->getRenderer(), text_surface);

    SDL_Rect healthRect;
    healthRect.x = SCREEN_WIDTH - text_surface->w - 10;
    healthRect.y = 0;
    healthRect.w = text_surface->w;
    healthRect.h = text_surface->h;

    SDL_FreeSurface(text_surface);

    SDL_RenderCopy(window->getRenderer(), text_texture, NULL, &healthRect);
}

void Game::renderPaused()
{
    std::string s = "Game Paused. ";
    SDL_Surface *text_surface = TTF_RenderText_Shaded(
        bigFont, s.c_str(), {0, 0, 0, 255}, {255, 255, 255, 255});
    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(window->getRenderer(), text_surface);

    SDL_Rect pausedRect;
    pausedRect.x = (SCREEN_WIDTH - text_surface->w) * 0.5;
    pausedRect.y = (SCREEN_HEIGHT - text_surface->h) * 0.5;
    pausedRect.w = text_surface->w;
    pausedRect.h = text_surface->h;

    SDL_FreeSurface(text_surface);

    SDL_RenderCopy(window->getRenderer(), text_texture, NULL, &pausedRect);
}

void Game::showGameOver()
{
    window->clear();
    std::string s = "Game Over! Your Score is: " + std::to_string(score);
    SDL_Surface *text_surface = TTF_RenderText_Shaded(
        bigFont, s.c_str(), {0, 0, 0, 255}, {255, 255, 255, 255});
    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(window->getRenderer(), text_surface);

    SDL_Rect scoreRect;
    scoreRect.x = (SCREEN_WIDTH - text_surface->w) * 0.5;
    scoreRect.y = (SCREEN_HEIGHT - text_surface->h) * 0.5;
    scoreRect.w = text_surface->w;
    scoreRect.h = text_surface->h;

    SDL_FreeSurface(text_surface);

    SDL_RenderCopy(window->getRenderer(), text_texture, NULL, &scoreRect);
    window->display();
}

void Game::destroy()
{
    window->destroy();
    TTF_CloseFont(smallFont);
    TTF_CloseFont(bigFont);
    free(window);
    free(hus);
}

bool Game::isCollide(Entity &first, Entity &second)
{
    if ((first.getXPosition() < (second.getXPosition() + second.getWidth())) &&
        ((first.getXPosition() + first.getWidth()) > second.getXPosition()) &&
        (first.getYPosition() < (second.getYPosition() + second.getHeight())) &&
        ((first.getYPosition() + first.getHeight()) > second.getYPosition()))
    {
        return true;
    }

    return false;
}

Game::~Game() { this->destroy(); }
