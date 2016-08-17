// System includes
#include <QQuickItem>
#include <QTimer>

// Interface for this file
#include "message_bar.h"

//  Created by Vikas pachdha
//Used from https://github.com/vikaspachdha/der_artikel

//******************************************************************************
/*! \brief Construtor.
 *
 *
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
MessageBar_C::MessageBar_C(QObject *parent) :
    QObject(parent),
    _message_bar_visible(false),
    _message_loop(0),
    _close_loop(0),
    _msg_bar(0),
    _min_duration_timer(0)
{
    _message_loop = new QEventLoop(this);
    _close_loop = new QEventLoop(this);
    _min_duration_timer = new QTimer(this);
    _min_duration_timer->setSingleShot(true);
}

//******************************************************************************
/*! \brief Returns message bar instance.
 *
 *
 *  \return MessageBar_C& : The message bar instance.
 ******************************************************************************/
MessageBar_C& MessageBar_C::instance()
{
    static MessageBar_C instance;
    return instance;
}

//******************************************************************************
/*! \brief Sets the visible state of the message bar.
 *
 *
 *  \param[in] visible : True to set state visible, false otherwise.
 ******************************************************************************/
void MessageBar_C::setMessageBarVisible(bool visible)
{
    if(_message_bar_visible != visible) {
        _message_bar_visible = visible;
        emit messageBarVisibleChanged();
    }
}

//******************************************************************************
/*! \brief Initializes the message bar.
 *
 *  \param[in] msg_bar : The message bar QML item.
 *  \param[in] settings : The settings instance.
 ******************************************************************************/
void MessageBar_C::init(QQuickItem *msg_bar)
{
    _msg_bar = msg_bar;
}

//******************************************************************************
/*! \brief Sets the accepted state of the message bar and closes the message bar.
 *
 *
 *  \param[in] accepted : True to set accepted, false otherwise.
 ******************************************************************************/
void MessageBar_C::setAccepted(bool accepted)
{
    if(_msg_bar->property("buttons_visible").toBool()) {
        MessageBar_C& msg_bar_instance = instance();
        msg_bar_instance._accepted = accepted;
        closeMsg();
    }
}

//******************************************************************************
/*! \brief Shows the message bar and it remains visible untill  either \ref
 *  MessageBar_C::closeMsg() is not called or user does not reponds using accept
 *  and reject button. Use the api to input the decision from user.
 *
 *
 *  \param[in] title : The message headline.
 *  \param[in] msg : The message detail text.
 *  \param[in] accept_str : The accept button text. Default is "ok".
 *  \param[in] reject_str : The reject button text. Default is "Cancel".
 *  \param[in] type : Type of message bar.
 *
 *  \return MessageBar_C::RetrunType_TP Accepted state.
 *
 *  \see \ref MessageBar_C::MsgType_TP & MessageBar_C::RetrunType_TP
 ******************************************************************************/
MessageBar_C::RetrunType_TP MessageBar_C::showMsg(QString title, QString msg, QString accept_str, QString reject_str, MessageBar_C::MsgType_TP type)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"showMessage",
                                  Q_ARG(QVariant,title),
                                  Q_ARG(QVariant,msg),
                                  Q_ARG(QVariant,-1),
                                  Q_ARG(QVariant,type),
                                  Q_ARG(QVariant,accept_str.isEmpty() ? QVariant() : accept_str),
                                  Q_ARG(QVariant,reject_str.isEmpty() ? QVariant() : reject_str));
        if(!msg_bar_instance._message_loop->isRunning()) {
            msg_bar_instance._message_loop->exec();
        }
    } else {

    }
    return msg_bar_instance._accepted ? ACCEPTED : REJECTED;
}

//******************************************************************************
/*! \brief Shows the message bar with the given message and details. The message
 *  bar is automatic and closes after duration msecs.
 *
 *
 *  \param[in] title : The message headline.
 *  \param[in] msg : The message detail text.
 *  \param[in] duration : The message bar closes after duration msecs.
 *  \param[in] type : Type of message bar.
 *
 *  \see \ref MessageBar_C::MsgType_TP
 ******************************************************************************/
void MessageBar_C::showMsg(QString title, QString msg, int duration, MessageBar_C::MsgType_TP type)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        QVariant null;
        QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"showMessage",
                                  Q_ARG(QVariant,title),
                                  Q_ARG(QVariant,msg),
                                  Q_ARG(QVariant,duration),
                                  Q_ARG(QVariant,type),
                                  Q_ARG(QVariant,null),
                                  Q_ARG(QVariant,null));
    } else {

    }
}

//******************************************************************************
/*! \brief Shows the message bar and it remains visible untill \ref MessageBar_C::closeMsg()
 *  is not called. Use the api when a background task is to be performed restricting
 *  user interaction.
 *
 *
 *  \param[in] title : The message headline.
 *  \param[in] msg : The message detail text.
 *  \param[in] min_duration : The minimum duration for which message is visible.
 *  \param[in] type : Type of message bar.
 *
 *  \see \ref MessageBar_C::MsgType_TP
 ******************************************************************************/
void MessageBar_C::showMsgAsync(QString title, QString msg, int min_duration, MessageBar_C::MsgType_TP type)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        QVariant null;
        QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"showMessage",
                                  Q_ARG(QVariant,title),
                                  Q_ARG(QVariant,msg),
                                  Q_ARG(QVariant,-1),
                                  Q_ARG(QVariant,type),
                                  Q_ARG(QVariant,null),
                                  Q_ARG(QVariant,null));

        // Let the message bar show for some time.
        QTimer::singleShot(400 + 200,msg_bar_instance._message_loop,SLOT(quit()));
        if(!msg_bar_instance._message_loop->isRunning()) {
            msg_bar_instance._message_loop->exec();
        }

        if(min_duration > 0) {
            msg_bar_instance._min_duration_timer->stop();
            msg_bar_instance._min_duration_timer->setInterval(min_duration);
            msg_bar_instance._min_duration_timer->start();
        }

    } else {

    }
}

//******************************************************************************
/*! \brief Updates the message string on message bar.
 *
 *
 *  \param[in] msg : The message detail text.
 ******************************************************************************/
void MessageBar_C::setMessage(QString msg)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        msg_bar_instance._msg_bar->setProperty("message_txt",msg);
    } else {

    }
}

//******************************************************************************
/*! \brief Updates the progress bar value on message bar.
 *
 *
 *  \param[in] progress : Progress value. Should be between 0 and 1 where 1 is 100%.
 ******************************************************************************/
void MessageBar_C::setProgress(double progress)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"setProgress",Q_ARG(QVariant,progress));
    } else {

    }
}

//******************************************************************************
/*! \brief Closes the message bar. Method returns only when message bar is closed.
 *
 ******************************************************************************/
void MessageBar_C::closeMsg()
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._min_duration_timer->isActive()) {
        QTimer::singleShot(msg_bar_instance._min_duration_timer->remainingTime(),&instance(),SLOT(closeMsg()));
    } else {
        if(msg_bar_instance._msg_bar) {
            // Let the message bar show for some time.
            QTimer::singleShot(500,msg_bar_instance._close_loop,SLOT(quit()));
            if(!msg_bar_instance._close_loop->isRunning()) {
                msg_bar_instance._close_loop->exec();
            }
            QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"closeMessage");
        } else {

        }

        // Don't return until message bar is hidden.
        QTimer::singleShot(400 + 100,msg_bar_instance._close_loop,SLOT(quit()));
        if(!msg_bar_instance._close_loop->isRunning()) {
            msg_bar_instance._close_loop->exec();
        }

        if(msg_bar_instance._message_loop->isRunning()) {
            msg_bar_instance._message_loop->quit();
        }
    }
}
