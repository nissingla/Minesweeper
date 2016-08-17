#include <QApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickItem>
#include <QtQml>
#include <iostream>

#include "gamemanager.h"
#include "gamemodel.h"
#include "message_bar.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<QAbstractItemModel>();
    qmlRegisterUncreatableType<GameManager>("com.example.qmlcomponents", 1, 0, "Manager","");
    qmlRegisterUncreatableType<MessageBar_C>("com.example.qmlcomponents", 1, 0, "MessageBar","");

    QQmlApplicationEngine* app_engine = new QQmlApplicationEngine;
    QQmlContext* root_context = app_engine->rootContext();

    GameManager* manager = new GameManager(root_context);

    root_context->setContextProperty("manager", manager);
    root_context->setContextProperty("gameModel", manager->getGameModel());
    root_context->setContextProperty("messageBarInstance",&MessageBar_C::instance());

    QQmlComponent component(app_engine,QUrl("qrc:/main.qml"),&app);
    QObject* root_item = component.create();
    manager->setRootQuickItem(root_item);
    int returnCode = app.exec();

    delete manager;
    delete app_engine;

    return returnCode;
}

