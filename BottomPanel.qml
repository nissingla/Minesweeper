import QtQuick 2.5

Item {
    id: bottomPanel
    property int shadow_offset:4
    signal quitButtonClicked

    Rectangle {
        id: background_shadow
        x:background_image.x + shadow_offset
        y:background_image.y + shadow_offset
        width:background_image.width
        height:background_image.height
        radius:6
        color: "black"
        opacity:0.8
    }

    Rectangle {
        id: background_image
        anchors.fill: parent
        radius:6
        color: "#65779B"

        Rectangle{
            id: quitButton
            anchors.centerIn: parent
            color: "transparent"
            width: 32
            height: 32
            Image{
                id: quitImage
                anchors.fill: parent
                source: "qrc:/Resources/quit_active.png"
            }
            MouseArea{
                id: mouseArea
                anchors.fill: parent
                onClicked:{
                    bottomPanel.quitButtonClicked()
                }
            }
        }
    }
}
