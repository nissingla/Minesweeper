
//  Created by Vikas pachdha
//Used from https://github.com/vikaspachdha/der_artikel

#ifndef MESSAGE_BAR_H
#define MESSAGE_BAR_H

// System includes
#include <QObject>
#include <QEventLoop>

// Forward declarations
class QQuickItem;
class QTimer;

class MessageBar_C : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MessageBar_C)
    Q_ENUMS(MsgType_TP)
    Q_ENUMS(RetrunType_TP)
    Q_PROPERTY(bool message_bar_visible READ messageBarVisible WRITE setMessageBarVisible NOTIFY messageBarVisibleChanged)
public:
    //! Message bar type.
    //! <ul>
    //! <li> INFO : Information message bar. </li>
    //! <li> WARNING : Warning message bar. </li>
    //! <li> ERROR : Error message bar. </li>
    //! </ul>
    enum MsgType_TP
    {
        INFO = 1,
        WARNING,
        ERROR,
    };

    //! Message bar accepted states.
    //! <ul>
    //! <li> ACCEPTED : Message bar is accepted. </li>
    //! <li> REJECTED : Message bar is rejected. </li>
    //! </ul>
    enum RetrunType_TP
    {
        ACCEPTED,
        REJECTED
    };

private:
    explicit MessageBar_C(QObject *parent = 0);

public:
    static MessageBar_C& instance();

    //! Returns True if message bar is visible, false otherwise.
    bool messageBarVisible() const { return _message_bar_visible; }
    void setMessageBarVisible(bool visible);

    void init(QQuickItem* msg_bar);

    Q_INVOKABLE void setAccepted(bool accepted);

    Q_INVOKABLE static RetrunType_TP showMsg(QString title, QString msg,
                                     QString accept_str = tr("Ok"),
                                     QString reject_str = tr("Cancel"),
                                     MsgType_TP type = INFO);

    Q_INVOKABLE static void showMsg(QString title, QString msg,
                            int duration,
                            MsgType_TP type = INFO);

    Q_INVOKABLE static void showMsgAsync(QString title, QString msg, int min_duration = -1,
                                 MsgType_TP type = INFO);

    Q_INVOKABLE static void setMessage(QString msg);

    Q_INVOKABLE static void setProgress(double progress);

public slots:
    static void closeMsg();

signals:
    //! Emitted on message bar visibility.
    void messageBarVisibleChanged();

private:
    //! Message bar visible flag
    bool _message_bar_visible;

    //! Event loop for message bar.
    QEventLoop* _message_loop;

    //! Event loop for message bar.
    QEventLoop* _close_loop;

    //! Message bar QML item
    QQuickItem* _msg_bar;

    //! Accepted state.
    bool _accepted;

    QTimer* _min_duration_timer;
};

#endif // MESSAGE_BAR_H
