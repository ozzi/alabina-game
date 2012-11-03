// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: mainWindow
    property string menuSelector: "mainMenu"
    //anchors.centerIn: parent
    width: 1280
    height: 1024
    MenuBackground {}
    ActiveScreen {
        anchors.fill: parent
        menuItemName: "mainMenu"
        menuSelectorName: mainWindow.menuSelector
        Column {
            anchors.centerIn: parent
            spacing: 30

            StartButton {
                buttonText: qsTr("Новая игра")
                width: 400
                height: 100
                onButtonPressed: mainWindow.menuSelector = "newGame"
            }

            StartButton {
                width: 400
                height: 100
                buttonText: qsTr("Таблица рекордов")
                onButtonPressed: mainWindow.menuSelector = "records"
            }

            StartButton {
                width: 400
                height: 100
                buttonText: qsTr("Правила")
                onButtonPressed: mainWindow.menuSelector = "rules"
            }
        }
    }

    ActiveScreen {
        anchors.fill: parent
        menuItemName: "newGame"
        menuSelectorName: mainWindow.menuSelector
        NewGame {
            anchors.fill: parent
        }
    }

    ActiveScreen {
        anchors.fill: parent
        menuItemName: "rules"
        menuSelectorName: mainWindow.menuSelector
        Rules {
            anchors.centerIn: parent
        }
    }

    ActiveScreen {
        anchors.fill: parent
        menuItemName: "records"
        menuSelectorName: mainWindow.menuSelector
        Records {
            anchors.centerIn: parent
        }
    }
}
