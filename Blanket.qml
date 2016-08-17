import QtQuick 2.5

Item {
    property bool showBlanket: false
    Rectangle {
        id:rect
        anchors.fill: parent
        color:"#000000"
        opacity:0
        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

    MouseArea {
        anchors.fill: parent
        visible: showBlanket
    }

   onShowBlanketChanged: {
       if(showBlanket === true) {
           rect.opacity = 0.7
       } else {
           rect.opacity = 0
       }
   }
}
