#include "gamemodel.h"

#include "gamemanager.h"
#include "igameplayingalgo.h"
#include "message_bar.h"

GameModel::GameModel(GameManager *parent, IGamePlayingAlgo* pGamePlayingAlgo):QAbstractListModel(parent)
  , mpGameManager(parent)
  , mpGamePlayingAlgo(pGamePlayingAlgo)
  , gameBoard(NULL)
{
    rows = mpGameManager->getNoOfRows();
    columns = mpGameManager->getNoOfColumns();
    initializeBoard();
    connect(mpGameManager, SIGNAL(gameLevelChanged()), this, SLOT(resetGame()));
}

GameModel::~GameModel()
{
    if(gameBoard != NULL)
        free(gameBoard);

    gameBoard = NULL;
}

QVariant GameModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)
    QVariant data;

    if(index.isValid()) {
        int row = index.row();
        switch (role) {
        case VALUE:
        {
            QChar value;
            int x = row / rows;
            int y = row % columns;
            value = QChar(*(gameBoard + x * columns + y));
            data = value;
            break;
        }
        case IMGSOURCE:
        {
            char value;
            int x = row / rows;
            int y = row % columns;
            value = *(gameBoard + x * columns + y);
            QString strPrefix = "qrc:/images/Resources/Number_";
            QString strSuffix = "_Icon_32.png";
            QString imgSource= "";
            if(value == '-')
                imgSource = "";
            else if(value == '0')
                imgSource = "qrc:/images/Resources/flag_32_32.png";
            else if(value == '*')
                imgSource = "qrc:/images/Resources/bomb_32_32.png";
            else if(value == '#')
                imgSource = "qrc:/images/Resources/flag_32_32.png";
            else
                imgSource = strPrefix + value + strSuffix;

            data = imgSource;
            break;
        }
        default:
            break;
        }
    }
    return data;
}

int GameModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return rows * columns;
}

QHash<int, QByteArray> GameModel::roleNames() const
{
    QHash<int,QByteArray> roleNames;
    roleNames[VALUE] = "value";
    roleNames[SELECTED] = "selected";
    roleNames[IMGSOURCE] = "imgSource";
    return roleNames;
}

Qt::ItemFlags GameModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    Qt::ItemFlags flags;
    flags = Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    return flags;
}

bool GameModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(value)
    if(role == SELECTED)
    {
        bool bRightClick = value.toBool();
        if(!mpGameManager->gameInProgress())
            mpGameManager->setGameInProgress(true);
        int row = index.row();
        int x = row / rows;
        int y = row % columns;
        GameManager::GAMESTATUS gameStatus = mpGamePlayingAlgo->playGame(gameBoard, x, y, !bRightClick);

        QModelIndex startIndex = createIndex(0, 0);
        QModelIndex endIndex = createIndex(rows * columns - 1, 0);
        emit dataChanged(startIndex, endIndex);
        //If game is not finished yet continue playing
        if(gameStatus == GameManager::NOTFINISHED)
        {

        }
        else
        {
            //ShowMessage to the user that he has won or lost and when he press Ok from Message box clear the grid
            if(gameStatus == GameManager::WON)
            {
                MessageBar_C::showMsg(QString("You have won!!"), "");
            }
            else
            {
                MessageBar_C::showMsg(QString("You have lost!!"), "");
            }
            resetGame();
        }
        return true;
    }
    return false;
}

void GameModel::initializeBoard()
{
    beginResetModel();
    if(gameBoard != NULL)
        free(gameBoard);

    gameBoard = (char*)malloc(rows * columns * sizeof(char));
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            *(gameBoard + i * columns + j) = '-';
        }
    }
    endResetModel();
}

void GameModel::resetGame()
{
    mpGameManager->setGameInProgress(false);
    rows = mpGameManager->getNoOfRows();
    columns = mpGameManager->getNoOfColumns();

    emit sideChanged();
    initializeBoard();
    mpGamePlayingAlgo->init();
}
