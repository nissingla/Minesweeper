import QtQuick 2.3
import QtQuick.Window 2.2

import com.example.qmlcomponents 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 580
    minimumHeight:480
    minimumWidth: 640
    title:"Minesweeper"

    Image{
        id: root
        anchors.fill: parent
        source: "qrc:/Resources/alt_background_texture.png"

        Title_bar{
            id: titleBar
            titleText: "Minesweeper"
            anchors.leftMargin: 3
            anchors.rightMargin: 5
        }

        Left_Panel{
            id: leftPanel
            anchors.top: titleBar.bottom
            anchors.topMargin: 3
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.bottom: bottomPanel.top
            anchors.bottomMargin: 3
            width: 110

            Button{
                id: button1
                buttonText: "Beginner"
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 10

                onButtonClicked: {
                    manager.gameLevel = Manager.BEGINNER
                }
            }
            Button{
                id: button2
                buttonText: "Intermediate"
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: button1.bottom
                anchors.topMargin: 25

                onButtonClicked: {
                    manager.gameLevel = Manager.INTERMEDIATE
                }
            }
            Button{
                id: button3
                buttonText: "Advanced"
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: button2.bottom
                anchors.topMargin: 25

                onButtonClicked: {
                    manager.gameLevel = Manager.ADVANCED
                }
            }

            Rectangle{
                id: resetGameRect
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"
                width: 48
                height: 48
                Image{
                    anchors.fill: parent
                    source: "qrc:/images/Resources/Reset_game.png"
                }
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        manager.resetGame()
                    }
                    onEntered: {

                    }
                }
            }
        }

        BottomPanel{
            id: bottomPanel
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            width: 110
            height: 90

            onQuitButtonClicked: {
                manager.quit();
            }
        }

        Item{
            id: dummyItem
            anchors.left: leftPanel.right
            anchors.right: parent.right
            anchors.top: titleBar.bottom
            anchors.bottom: parent.bottom
            anchors.margins: 5
        }

        GridView{
            id: playingGrid
            property int gridCellWidth: Math.min(dummyItem.width, dummyItem.height)/gameModel.side

            model: gameModel
            cellWidth: gridCellWidth
            cellHeight: gridCellWidth
            width: gridCellWidth * gameModel.side
            anchors.top: titleBar.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            anchors.left: leftPanel.right
            anchors.leftMargin: 10
            delegate: Rectangle{
                color: (value === '0') ? "darkgrey" : "#C3C3C3"
                width: playingGrid.gridCellWidth
                height: playingGrid.gridCellWidth
                border.color: "black"
                border.width: 1
                Image{
                    anchors.fill: parent
                    visible: value != '-' && value != '0'
                    source: imgSource
                }
                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
                        console.log(mouse.button)
                        if(mouse.button === Qt.LeftButton)
                            selected = true
                        if(mouse.button === Qt.RightButton)
                            selected = false
                    }
                }
            }
        }
    }

    Message_bar{
        id: msgBar
        anchors.fill: parent
    }

    function getMessageBar()
    {
        return msgBar;
    }
}

