#ifndef GAME_PLAYING_ALGO_H
#define GAME_PLAYING_ALGO_H

#include "igameplayingalgo.h"

class GameManager;

class game_playing_algo: public IGamePlayingAlgo
{
public:
    explicit game_playing_algo(GameManager* pGameManager);

    virtual ~game_playing_algo();
    virtual void init();

    virtual GameManager::GAMESTATUS playGame(char *board, int x, int y, bool rightClick);

private:
    //No of mines
    int c_mines;

    //Locating mines
    int *mines;

    //gameBoard
    char *gameBoard;

    //gameBoard
    char *flagBoard;

    //No of rows
    int rows;

    //No of colums
    int columns;

    //No of moves left for the player
    int movesLeft;

    //Used to track first move as if it is user first move clikcing on mine is also valid
    bool firstMove;

    GameManager* mpGameManager;


    //It will place the mines randomly on the playing baord
    void placeMines();

    void initializeBoard();

    int getNoOfMines(int row, int column);

    bool isValid(int row, int column);

    bool gameHelper(char *board, int row, int column);

    bool replaceMine(int row, int column);

    bool isMine(int row, int column);

    bool isFlag(int row, int column);
};

#endif // GAME_PLAYING_ALGO_H
