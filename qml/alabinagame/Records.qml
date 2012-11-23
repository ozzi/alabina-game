// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 300
    height: 600
    radius: 30
    color: "green"
    opacity: 0.4

    ListView {
        anchors.fill: parent
        anchors.topMargin: 30
        model: cRecordsModel
        delegate: Item {
            width: parent.width - 60
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                text: recordName
                font.pointSize: 16
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
            }
            Text {
                text: recordPoints
                font.pointSize: 32
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
            }
        }
        spacing: 15
    }

    MouseArea {
        anchors.fill: parent
        onClicked: mainWindow.menuSelector = "mainMenu"
    }
}
