//John Conway's "Game Of Life"
//Date Created: 7/29/2020 2:00 AM
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#define WIDTH 800
#define HEIGHT 600
using namespace std;

//Sets the initial color of each block
void initSqaure(int* arr[])
{
    const int ROWS = HEIGHT / 5;
    const int COLS = WIDTH / 5;
    int count = 0;
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            int doa = rand() % 3;
            if (doa == 0)
            {
                arr[row][col] = 1;
                count = 0;
            }
            else
                arr[row][col] = 0;
        }
    }
}

//Changes cells
void cellAuto(int* arr[])
{
    int count = 0;
    const int ROWS = HEIGHT / 5;
    const int COLS = WIDTH / 5;

    auto coords = [&](int x, int y)
    {
        if (x < 0 || y < 0 || x >= ROWS || y >= COLS)
            return(0);
        if (arr[x][y] == 1)
            return(1);
        else
            return(0);
    };

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (arr[row][col] == 1)
            {
                count = coords((row - 1), (col - 1))
                    +coords((row - 1), col)
                    + coords((row - 1), (col + 1))
                    + coords(row, (col - 1))
                    + coords(row, (col + 1))
                    + coords((row + 1), (col - 1))
                    + coords((row + 1), col)
                    + coords((row + 1), (col + 1));

                if (count > 3 || count < 2)
                {
                    arr[row][col] = 0;
                }
                count = 0;
            }
            else
            {
                count = coords((row - 1), (col - 1))
                    + coords((row - 1), col)
                    + coords((row - 1), (col + 1))
                    + coords(row, (col - 1))
                    + coords(row, (col + 1))
                    + coords((row + 1), (col - 1))
                    + coords((row + 1), col)
                    + coords((row + 1), (col + 1));

                if (count == 3)
                {
                    arr[row][col] = 1;
                }
                count = 0;
            }
        }
    }
}

//Sets size and position of each cell
void setPosition(sf::RectangleShape& square, const float x, const float y)
{
    square.setSize(sf::Vector2f(5, 5));
    square.setPosition(sf::Vector2f(x, y));
}

//Prints all the cells to window
void printCells(sf::RectangleShape& square, sf::RenderWindow& window, int* arr[])
{
    const int ROWS = HEIGHT / 5;
    const int COLS = WIDTH / 5;
    float xpos = 0;
    float ypos = 0;

    for (int row = 0; row < ROWS; row++)
    {
        ypos += 5;
        for (int col = 0; col < COLS; col++)
        {
            if (arr[row][col] == 0)
                square.setFillColor(sf::Color::Black);
            else
            {
                //square.setFillColor(sf::Color(0, 202, 211));
                int color = rand() % 4;
                switch (color)
                {
                case 0:
                    square.setFillColor(sf::Color(255, 153, 51));
                    break; 
                case 1:
                    square.setFillColor(sf::Color(124, 252, 0));
                    break;
                case 2:
                    square.setFillColor(sf::Color(0, 255, 255));
                    break;
                case 3:
                    square.setFillColor(sf::Color(186, 85, 211));
                    break;
                default:
                    square.setFillColor(sf::Color::White);
                }
            }
            setPosition(square, xpos, ypos);
            window.draw(square);
            xpos += 5;
        }
        xpos = 0;
    }
}

typedef int* Arrptr;
int main()
{
    const int ROWS = HEIGHT / 5;
    const int COLS = WIDTH / 5;

    Arrptr* arr = new Arrptr[ROWS];

    for (int index = 0; index < ROWS; index++)
        arr[index] = new int[COLS];

    int color = 0;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "John Conway's \"Game Of Life\"");
    sf::RectangleShape square;

    initSqaure(arr);

    window.setFramerateLimit(50);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        printCells(square, window, arr);
        cellAuto(arr);
        window.display();
    }

    { // delete dynamic pointers
        for (int index = 0; index < ROWS; index++)
            delete[] arr[index];
        delete[] arr;
    }
    return 0;
}