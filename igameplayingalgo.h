#ifndef IGAMEPLAYINGALGO_H
#define IGAMEPLAYINGALGO_H

#include "gamemanager.h"

class IGamePlayingAlgo
{
public:
    virtual void init() = 0;
    virtual GameManager::GAMESTATUS playGame(char *board, int x, int y, bool rightClick) = 0;
};

#endif // IGAMEPLAYINGALGO_H
