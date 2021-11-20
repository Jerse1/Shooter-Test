#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <vector>

bool _isRunning;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_KeyCode Key = SDLK_RIGHT;
int Speed = 20;

int xscreen = SDL_WINDOWPOS_CENTERED;
int yscreen = SDL_WINDOWPOS_CENTERED;

int mouse_x, mouse_y;

bool mouseDown;

short int windowWidth = 800;
short int windowHeight = 600;

SDL_Rect P0;
SDL_Rect P1;
SDL_Rect P2;
SDL_Rect P3;

class Vector2
{
    int x, y;

    Vector2(int = 0, int = 0);
    ~Vector2();

    inline Vector2 &Vector2::operator=(const Vector2 &v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }
    inline Vector2 &Vector2::operator=(const int &f)
    {
        x = f;
        y = f;
        return *this;
    }
    inline Vector2 &Vector2::operator-(void)
    {
        x = -x;
        y = -y;
        return *this;
    }
    inline bool Vector2::operator==(const Vector2 &v) const { return (x == v.x) && (y == v.y); }
    inline bool Vector2::operator!=(const Vector2 &v) const { return (x != v.x) || (y != v.y); }

    // Vector2 and Vector2 Operations
    inline const Vector2 Vector2::operator+(const Vector2 &v) const
    {
        return Vector2(x + v.x, y + v.y);
    }
    inline const Vector2 Vector2::operator-(const Vector2 &v) const
    {
        return Vector2(x - v.x, y - v.y);
    }
    inline const Vector2 Vector2::operator*(const Vector2 &v) const
    {
        return Vector2(x * v.x, y * v.y);
    }
    inline const Vector2 Vector2::operator/(const Vector2 &v) const
    {
        return Vector2(x / v.x, y / v.y);
    }

    inline Vector2 &Vector2::operator+=(const Vector2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    inline Vector2 &Vector2::operator-=(const Vector2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    inline Vector2 &Vector2::operator*=(const Vector2 &v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }
    inline Vector2 &Vector2::operator/=(const Vector2 &v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    // Vector2 Operations
    inline const Vector2 Vector2::operator+(int v) const { return Vector2(x + v, y + v); }
    inline const Vector2 Vector2::operator-(int v) const { return Vector2(x - v, y - v); }
    inline const Vector2 Vector2::operator*(int v) const { return Vector2(x * v, y * v); }
    inline const Vector2 Vector2::operator/(int v) const { return Vector2(x / v, y / v); }

    // This Operations
    inline Vector2 &Vector2::operator+=(int v)
    {
        x += v;
        y += v;
        return *this;
    }
    inline Vector2 &Vector2::operator-=(int v)
    {
        x -= v;
        y -= v;
        return *this;
    }
    inline Vector2 &Vector2::operator*=(int v)
    {
        x *= v;
        y *= v;
        return *this;
    }
    inline Vector2 &Vector2::operator/=(int v)
    {
        x /= v;
        y /= v;
        return *this;
    }
};

Vector2::Vector2(int xVal = 0, int yVal = 0) : x(xVal), y(yVal){};

class Bullet
{
    Vector2 Position;
    Vector2 Velocity;
    Vector2 Direction;
    void Spawn()
    {
    }
};


void Initialize(const char *title, bool fullscreen);

void handleEvents();
void Update();
void Render();
void Clean();

bool isRunning();

int getPt(int n1, int n2, float perc)
{
    int diff = n2 - n1;

    return n1 + (diff * perc);
}

int main(int argc, char *argv[])
{

    Initialize("Shooter Test", false);

    clock_t start, end;

    while (isRunning())
    {

        handleEvents();

        double time_since = double(clock() - start);

        int lastTailLength;

        if (time_since / 1000.0 > 0.003)
        {
            Update();
            Render();

            // std::cout << std::setprecision(3) << 1000 / time_since << std::endl;

            start += 3.0;
        }
    }

    Clean();

    return 0;
}

// TODO
void Initialize(const char *title, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Game has been initialized!" << std::endl;

        window = SDL_CreateWindow(title, xscreen, yscreen, windowWidth, windowHeight, flags);
        if (window)
        {
            std::cout << "Window has been successfully created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer has been successfully created!" << std::endl;
        }

        _isRunning = true;
    }
};

bool isRunning()
{
    return _isRunning;
}

void handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        _isRunning = false;
        break;
    case SDL_MOUSEBUTTONUP:

        if (mouseDown == true)
        {
            mouseDown = false;
            std::cout << "mouse up\n";
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (mouseDown == false)
        {
            mouseDown = true;
            std::cout << "mouse down\n";
        }
        break;
    default:
        break;
    }
}

void Update()
{
    SDL_GetMouseState(&mouse_x, &mouse_y);
}

void Render()
{
    SDL_RenderClear(renderer);
    // Rendering n shit;

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

    SDL_RenderPresent(renderer);
}

void Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game has been successfully cleaned!";
};