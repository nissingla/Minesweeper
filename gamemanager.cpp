#include "gamemanager.h"
#include "game_playing_algo.h"
#include "gamemodel.h"

#include <QQuickItem>
#include "message_bar.h"

#include <QApplication>
#include <QToolTip>

GameManager::GameManager(QQmlContext* rootContext, QObject* parent):
    QObject(parent),
    currentGameLevel(BEGINNER),
    mpRootItem(NULL),
    mpRootContext(rootContext),
    mpGamePlayingAlgo(NULL),
    mpGameModel(NULL),
    mbGameInProgress(false)
{
    mpGamePlayingAlgo = new game_playing_algo(this);
    mpGameModel = new GameModel(this, mpGamePlayingAlgo);
}

GameManager::~GameManager()
{
    if(mpGamePlayingAlgo != NULL)
    {
        delete mpGamePlayingAlgo;
        mpGamePlayingAlgo = NULL;
    }
    if(mpGameModel != NULL)
    {
        delete mpGameModel;
        mpGameModel = NULL;
    }
}

void GameManager::setGameLevel(GAMELEVEL gameLevel)
{
    if(gameLevel != currentGameLevel)
    {
        if(mbGameInProgress)
        {
            if(MessageBar_C::showMsg(QString("Do you really want to change the game level?"), QString("Your progress will be lost!!!")) == MessageBar_C::REJECTED)
            {
                return;
            }
        }
        currentGameLevel = gameLevel;
        emit gameLevelChanged();
    }
}

int GameManager::getNoOfRows()
{
    int rows;
    if(currentGameLevel == BEGINNER)
        rows = 9;
    if(currentGameLevel == INTERMEDIATE)
        rows = 16;
    if(currentGameLevel == ADVANCED)
        rows = 24;

    return rows;
}

int GameManager::getNoOfColumns()
{
    int columns;
    if(currentGameLevel == BEGINNER)
        columns = 9;
    if(currentGameLevel == INTERMEDIATE)
        columns = 16;
    if(currentGameLevel == ADVANCED)
        columns = 24;

    return columns;
}

int GameManager::getNoOfMines()
{
    int mines;
    if(currentGameLevel == BEGINNER)
        mines = 10;
    if(currentGameLevel == INTERMEDIATE)
        mines = 40;
    if(currentGameLevel == ADVANCED)
        mines = 99;

    return mines;
}

void GameManager::setRootQuickItem(QObject *root_Item)
{
    mpRootItem = root_Item;
    QVariant msg_bar_obj;
    QQuickItem* msg_bar_item = 0;
    QMetaObject::invokeMethod(root_Item,"getMessageBar",Q_RETURN_ARG(QVariant,msg_bar_obj));
    msg_bar_item = msg_bar_obj.value<QQuickItem*>();
    MessageBar_C::instance().init(msg_bar_item);
}

void GameManager::quit()
{
    if(MessageBar_C::showMsg(QString("Do you really want to quit?"), "") == MessageBar_C::ACCEPTED)
    {
        QApplication::quit();
    }
}

void GameManager::resetGame()
{
    if(mpGameModel)
    {
        if(mbGameInProgress)
        {
            if(MessageBar_C::showMsg(QString("Do you really want to reset the game?"), QString("Your progress will be lost!!!")) == MessageBar_C::REJECTED)
            {
                return;
            }
        }
        mpGameModel->resetGame();
    }
}

void GameManager::showToolTip(const QString& toolTip, const int& x, const int& y)
{
    QToolTip::showText(QPoint(x, y), toolTip);
}
