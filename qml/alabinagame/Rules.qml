// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 600
    height: parent.height * 0.7
    radius: 30
    color: "green"
    opacity: 0.6

    Column {
        anchors.centerIn: parent
        spacing: 10
        Repeater {
            model: 20
            Text {
                text: qsTr("Много текста текста много текста текста")
                font.pointSize: 18
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: mainWindow.menuSelector = "mainMenu"
    }
}
