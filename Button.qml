import QtQuick 2.5

Item {
    id: buttonRoot
    property alias buttonText: buttonText.text
    signal buttonClicked
    width: buttonRect.width
    height: buttonRect.height
    Rectangle{
        id: buttonRect
        radius: 4
        gradient: Gradient {
            GradientStop {position: 0  ;color: "#AFAFAF"}
            GradientStop {position: 0.2;color: mouseArea.pressed ? "E7E7E7":"#AFAFAF"}
            GradientStop {position: 1;color: "#E7E7E7"}
        }
        width: buttonText.width + 6
        height: buttonText.height + 6
        Text{
            id: buttonText
            anchors.centerIn: parent
            color: "white"
            font.pointSize: 12
            font.bold: true
        }
    }
    MouseArea{
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            buttonRoot.buttonClicked()
        }
    }
}

