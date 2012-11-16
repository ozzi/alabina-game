// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    signal nextLevel
    signal showMenu
    signal showGallery
    signal showDescription
    signal showTest
    ListView {
        id: resultsList
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: sideMenu.left
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        spacing: 100
        model: cResultModel
        header: BaseText {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Total : ") + cResultModel.pointsTotal
        }
        delegate: Item {
            width: resultsList.width
            height: 50
            BaseText {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                text: index
            }
            BaseText {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                text: resultPoints
            }
        }
    }

    Column {
        id: sideMenu
        width: 200
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.right: parent.right
        anchors.rightMargin: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        spacing: 100
        StartButton {
            width: parent.width
            height: 50
            buttonText: "next level"
            onButtonPressed: nextLevel()
        }
        StartButton {
            width: parent.width
            height: 50
            buttonText: "description"
            onButtonPressed: showDescription()
        }
        StartButton {
            width: parent.width
            height: 50
            buttonText: "gallery"
            onButtonPressed: showGallery()
        }
        StartButton {
            width: parent.width
            height: 50
            buttonText: "test"
            onButtonPressed: showTest()
        }
        StartButton {
            width: parent.width
            height: 50
            buttonText: "menu"
            onButtonPressed: showMenu()
        }
    }
}
