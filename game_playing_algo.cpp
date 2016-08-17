#include "game_playing_algo.h"
#include <stdio.h>
#include <stdlib.h>
#include "gamemanager.h"
#include <math.h>
#include <QDebug>

game_playing_algo::game_playing_algo(GameManager* pGameManager)
{
    mines = NULL;
    gameBoard = NULL;
    mpGameManager = pGameManager;
    firstMove = true;
    init();
}

game_playing_algo::~game_playing_algo()
{
    free(mines);
    mines = NULL;
    free(gameBoard);
    gameBoard = NULL;
}

void game_playing_algo::init()
{
    this->c_mines = mpGameManager->getNoOfMines();
    this->rows = mpGameManager->getNoOfRows();
    this->columns = mpGameManager->getNoOfColumns();

    if(mines != NULL)
    {
        free(mines);
    }
    mines = (int *)malloc(c_mines * 2 * sizeof(int));
    if(gameBoard != NULL)
    {
        free(gameBoard);
    }
    gameBoard = (char *)malloc(rows * columns * sizeof(char));
    flagBoard = (char *)malloc(rows * columns * sizeof(char));

    movesLeft = (rows * columns) - c_mines;
    firstMove = true;
    initializeBoard();
    placeMines();
}

bool game_playing_algo::gameHelper(char *board, int row, int column)
{
    if(*(board + row * columns + column) != '-' && *(board + row * columns + column) != '#')
        return false;

    if(*(gameBoard + row * columns + column) == '*')
    {
        *(board + row * columns + column) = '*';
        for(int i = 0; i < c_mines; i++)
        {
            int x = *(mines + i * 2 + 0);
            int y = *(mines + i * 2 + 1);
            *(board + (x) * columns + y) = '*';
        }
        return true;
    }

    else
    {
        int noOfMines = getNoOfMines(row, column);
        *(board + row * columns + column) = noOfMines + '0';

        movesLeft--;
        if(noOfMines == 0)
        {
            if(isValid(row - 1, column) && !isMine(row - 1, column) && !isFlag(row - 1, column))
                gameHelper(board, row - 1, column);

            if(isValid(row, column - 1) && !isMine(row, column - 1 && !isFlag(row, column - 1)))
                gameHelper(board, row, column - 1);

            if(isValid(row + 1, column) && !isMine(row + 1, column)  && !isFlag(row + 1, column))
                gameHelper(board, row + 1, column);

            if(isValid(row, column + 1) && !isMine(row, column + 1)  && !isFlag(row, column + 1))
                gameHelper(board, row, column + 1);

            if(isValid(row - 1, column - 1) && !isMine(row - 1, column - 1)  && !isFlag(row - 1, column - 1))
                gameHelper(board, row - 1, column - 1);

            if(isValid(row + 1, column + 1) && !isMine(row + 1, column + 1) && !isFlag(row + 1, column + 1))
                gameHelper(board, row + 1, column + 1);

            if(isValid(row - 1, column + 1) && !isMine(row - 1, column + 1) && !isFlag(row - 1, column + 1))
                gameHelper(board, row - 1, column + 1);

            if(isValid(row + 1, column - 1) && !isMine(row + 1, column - 1) && !isFlag(row + 1, column - 1))
                gameHelper(board, row + 1, column - 1);
        }
        return false;
    }
    return false;
}

GameManager::GAMESTATUS game_playing_algo::playGame(char *board, int x, int y, bool rightClick)
{
    bool gameOver = false;

    if(rightClick)
    {
        if(*(board + x * columns + y) == '-')
        {
            *(board + x * columns + y) = '#';
            *(flagBoard + x * columns + y) = '#';
        }
        return GameManager::NOTFINISHED;
    }

    //First time mine replace that
    if(*(gameBoard + x * columns + y) == '*' && isValid(x, y) && firstMove)
    {
        replaceMine(x, y);
    }

    firstMove = false;
    gameOver = gameHelper(board, x, y);

    if(gameOver && movesLeft != 0) //Lost
    {
        return GameManager::LOST;
    }
    else if(gameOver && movesLeft == 0) //Won
    {
        return GameManager::WON;
    }

    return GameManager::NOTFINISHED;
}

void game_playing_algo::placeMines()
{
    bool mark[rows*columns];

    memset(mark, false, sizeof (mark));

    for(int i = 0; i < c_mines;)
    {
        int random = rand()%(rows * columns);
        int x = random/rows;
        int y = random%columns;

        if(mark[random] == false)
        {
            *(gameBoard + x * columns + y) = '*';
            *(mines + i * 2 + 0) = x;
            *(mines + i * 2 + 1) = y;

            qDebug() << x << y;
            mark[random] = true;
            i++;
        }
    }
}

void game_playing_algo::initializeBoard()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            *(gameBoard + i * columns + j) = '-';
            *(flagBoard + i * columns + j) = '-';
        }
    }
}

int game_playing_algo::getNoOfMines(int row, int column)
{
    int noOfMines = 0;
    if(isValid(row - 1, column) && *(gameBoard + (row - 1) * columns + column) == '*')
        noOfMines++;

    if(isValid(row, column - 1) && *(gameBoard + (row) * columns + (column - 1)) == '*')
        noOfMines++;

    if(isValid(row + 1, column) && *(gameBoard + (row + 1) * columns + column) == '*')
        noOfMines++;

    if(isValid(row, column + 1) && *(gameBoard + (row) * columns + (column + 1)) == '*')
        noOfMines++;

    if(isValid(row - 1, column - 1) && *(gameBoard + (row - 1) * columns + (column - 1)) == '*')
        noOfMines++;

    if(isValid(row + 1, column + 1) && *(gameBoard + (row + 1) * columns + (column + 1)) == '*')
        noOfMines++;

    if(isValid(row - 1, column + 1) && *(gameBoard + (row - 1) * columns + (column + 1)) == '*')
        noOfMines++;

    if(isValid(row + 1, column - 1) && *(gameBoard + (row + 1) * columns + (column - 1)) == '*')
        noOfMines++;

    return noOfMines;
}

bool game_playing_algo::isValid(int row, int column)
{
    if(row < rows && column < columns && row >= 0 && column >= 0)
        return true;

    return false;
}

bool game_playing_algo::replaceMine(int row, int column)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(*(gameBoard + i * columns + j) != '*')
            {
                *(gameBoard + row * columns + column) = '-';
                *(gameBoard + i * columns + j) = '*';
                break;
            }
        }
    }

    return true;
}

bool game_playing_algo::isMine(int row, int column)
{
    if(*(gameBoard + row * columns + column) == '*')
        return true;

    return false;
}

bool game_playing_algo::isFlag(int row, int column)
{
    if(*(flagBoard + row * columns + column) == '#')
        return true;

    return false;
}
