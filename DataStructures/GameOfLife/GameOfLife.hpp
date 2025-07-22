#ifndef GAME_OF_LIFE_HPP
#define GAME_OF_LIFE_HPP

#include <iostream>
#include "array2d.hpp"
#include <thread>
#include <chrono>
#include <random>

using namespace data_structures;

class GameOfLife
{
public:
    GameOfLife(size_t rows, size_t columns);

    void run();
    void displayArray();
    int countNeighbors(size_t row, size_t column) const;
    void updateGeneration();
    void seedRandom(double probability);

private:
    Array2D<bool> gameBoard;
    Array2D<bool> nextGen;
    size_t rows;
    size_t columns;
};


GameOfLife::GameOfLife(size_t rows, size_t columns)
    : gameBoard(rows, columns), nextGen(rows, columns), rows(rows), columns(columns) {}


void GameOfLife::displayArray() {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            if (gameBoard[i][j])
            {
                std::cout << "[X]";
            }
            else
            {
                std::cout << "[ ]";
            }
        }
        std::cout << "\n";
    }
}

int GameOfLife::countNeighbors(size_t row, size_t column) const
{
    int counter = 0;

    int startRow = static_cast<int>(row) - 1;
    int endRow = static_cast<int>(row) + 1;
    int startCol = static_cast<int>(column) - 1;
    int endCol = static_cast<int>(column) + 1;

    for (int i = startRow; i <= endRow; ++i)
    {
        for (int j = startCol; j <= endCol; ++j)
        {
            if (i < 0 || i >= static_cast<int>(rows) || j < 0 || j >= static_cast<int>(columns))
                continue;

            if (i == static_cast<int>(row) && j == static_cast<int>(column))
                continue;

            if (gameBoard[static_cast<size_t>(i)][static_cast<size_t>(j)])

            {
                ++counter;
            }
        }
    }
    return counter;
}

void GameOfLife::updateGeneration()
{
    for (size_t row = 0; row < rows; ++row)
    {
	    for (size_t column = 0; column < columns; ++column)
	    {
            int aliveNeighbors = countNeighbors(row, column);

            if (gameBoard[row][column]) // Cell is alive
            {
                if (aliveNeighbors == 2 || aliveNeighbors == 3)
                    nextGen[row][column] = true;  // Lives
                else
                    nextGen[row][column] = false; // Dies
            }
            else // Cell is dead
            {
                if (aliveNeighbors == 3)
                    nextGen[row][column] = true;  // Born
                else
                    nextGen[row][column] = false; // Stays dead
            }
	    }
    }

    gameBoard = nextGen;
}

void GameOfLife::seedRandom(double probability)
{
    srand(time(nullptr));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j)
        {
            float num = static_cast<float>(rand()) / RAND_MAX;
            gameBoard[i][j] = (num < probability);
        }
    }
}

void GameOfLife::run() {
    seedRandom(0.5);

    for (int i = 0; i < 10; ++i)
    {
        displayArray();
        updateGeneration();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        system("CLS");
    }
}

#endif
