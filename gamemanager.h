#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QQmlContext>

class IGamePlayingAlgo;
class GameModel;

class GameManager: public QObject
{
    Q_OBJECT
    Q_ENUMS(GAMELEVEL)
    Q_ENUMS(GAMESTATUS)

    Q_PROPERTY(GAMELEVEL gameLevel READ gameLevel WRITE setGameLevel NOTIFY gameLevelChanged)
public:
    enum GAMELEVEL
    {
        BEGINNER = 0,
        INTERMEDIATE,
        ADVANCED
    };

    enum GAMESTATUS
    {
        WON = 0,
        LOST,
        NOTFINISHED
    };

    GameManager(QQmlContext* rootContext, QObject* parent = 0);
    virtual ~GameManager();
    GAMELEVEL gameLevel() { return currentGameLevel; }
    Q_INVOKABLE void setGameLevel(GAMELEVEL gameLevel);

    int getNoOfRows();
    int getNoOfColumns();
    int getNoOfMines();

    GameModel* getGameModel() { return mpGameModel; }

    void setRootQuickItem(QObject *root_Item);

    Q_INVOKABLE void quit();
    Q_INVOKABLE void resetGame();

    bool gameInProgress() { return mbGameInProgress; }
    void setGameInProgress(bool inProgress) { mbGameInProgress = inProgress; }

    Q_INVOKABLE void showToolTip(const QString& toopTip, const int& x, const int& y);
signals:
    void gameLevelChanged();

private:
    GAMELEVEL currentGameLevel;
    QQmlContext* mpRootContext;
    IGamePlayingAlgo* mpGamePlayingAlgo;
    GameModel* mpGameModel;

    bool mbGameInProgress;
    QObject *mpRootItem;
};

#endif // GAMEMANAGER_H
