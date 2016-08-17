import QtQuick 2.5

Item {
    id: title
    property int shadow_offset:4
    property alias titleText: titleText.text

    height: 100
    anchors.left: parent.left
    anchors.right: parent.right

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

        Text{
            id: titleText
            color: "white"
            font.pointSize: 22
            font.bold: true
            anchors.centerIn: parent
        }
    }
}
