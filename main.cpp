#include <iostream>
#include <conio.h>
#include <windows.h>
#include <deque>

enum Direction {UP, DOWN, LEFT, RIGHT};

class SnakeGame {
private:
    const int width = 20;
    const int height = 20;
    bool gameOver;
    int score;
    int fruitX, fruitY;
    int headX, headY;
    Direction dir;
    std::deque<std::pair<int, int>> snake;

public:
    SnakeGame() {
        gameOver = false;
        score = 0;
        headX = width / 2;
        headY = height / 2;
        dir = RIGHT;
        snake.push_front({headX, headY});
        placeFruit();
    }

    void draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            std::cout << "#";
        std::cout << std::endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    std::cout << "#";
                if (i == headY && j == headX)
                    std::cout << "O";
                else if (i == fruitY && j == fruitX)
                    std::cout << "F";
                else {
                    bool printSnake = false;
                    for (const auto &segment : snake) {
                        if (segment.first == j && segment.second == i) {
                            std::cout << "o";
                            printSnake = true;
                            break;
                        }
                    }
                    if (!printSnake)
                        std::cout << " ";
                }
                if (j == width - 1)
                    std::cout << "#";
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < width + 2; i++)
            std::cout << "#";
        std::cout << std::endl;
        std::cout << "Score: " << score << std::endl;
    }

    void input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                if (dir != DOWN)
                    dir = UP;
                break;
            case 's':
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'a':
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    void logic() {
        
        switch (dir) {
        case UP:
            headY--;
            break;
        case DOWN:
            headY++;
            break;
        case LEFT:
            headX--;
            break;
        case RIGHT:
            headX++;
            break;
        }

        if (headX < 0) headX = width-1;
        if (headX > width) headX = 0;
        if (headY < 0) headY = height-1;
        if (headY > height) headY = 0;

        for (const auto &segment : snake) {
            if (headX == segment.first && headY == segment.second)
                gameOver = true;
        }

        if (headX == fruitX && headY == fruitY) {
            score += 10;
            placeFruit();
            snake.push_front({headX, headY});
        } else {
            snake.push_front({headX, headY});
            snake.pop_back();
        }
    }

    bool isGameOver() {
        return gameOver;
    }

    void placeFruit() {
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    SnakeGame game;
    while (!game.isGameOver()) {
        game.draw();
        game.input();
        game.logic();
        Sleep(100); // Задержка для управления скоростью змейки
    }
    std::cout << "Game Over!" << std::endl;
    return 0;
}
