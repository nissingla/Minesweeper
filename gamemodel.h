#ifndef GAME_MODEL_H
#define GAME_MODEL_H

// System includes
#include <QAbstractListModel>

class GameManager;
class IGamePlayingAlgo;

class GameModel : public QAbstractListModel
{
    Q_OBJECT

    // Properties
    Q_PROPERTY(int side READ side NOTIFY sideChanged)

public:

    enum ROLES_TP {
        VALUE = Qt::UserRole,
        IMGSOURCE,
        SELECTED
    };

    explicit GameModel(GameManager *parent, IGamePlayingAlgo* pGamePlayingAlgo);
    ~GameModel();

    // QAbstarctItemModel Implementation.
public:
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int,QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    int side() { return rows; }
public slots:
    void resetGame();

signals:
    void sideChanged();

private:
    char *gameBoard;
    int rows;
    int columns;
    GameManager* mpGameManager;
    IGamePlayingAlgo* mpGamePlayingAlgo;

    void initializeBoard();
};

#endif // GAME_MODEL_H
