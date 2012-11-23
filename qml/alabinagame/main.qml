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
                id: newGameButton
                buttonText: qsTr("Новая игра")
                width: 400
                height: 100
            }

            StartButton {
                id: recordsButton
                width: 400
                height: 100
                buttonText: qsTr("Таблица рекордов")
            }

            StartButton {
                id: aboutButton
                width: 400
                height: 100
                buttonText: qsTr("О программе")
            }
        }
    }

    NewGame {
        id: newGameScreen
        anchors.fill: parent
        menuItemName: "newGame"
        menuSelectorName: mainWindow.menuSelector
    }

    ActiveScreen {
        id: recordsScreen
        anchors.fill: parent
        menuItemName: "records"
        menuSelectorName: mainWindow.menuSelector
        Records {
            anchors.centerIn: parent
        }
    }

    ActiveScreen {
        id: aboutScreen
        anchors.fill: parent
        menuItemName: "rules"
        menuSelectorName: mainWindow.menuSelector
        Rules {
            anchors.centerIn: parent
        }
    }
    function toggleNewGame()
    {
        cSessionModel.setDefaultUserName();
        newGameScreen.enter();
        menuSelector = "newGame";
    }
    function toggleRecords()
    {
        menuSelector = "records"
    }
    function toggleAbout()
    {
        menuSelector = "rules"
    }
    function toggleMainMenu()
    {
        menuSelector = "mainMenu"
    }

    Component.onCompleted: {
        newGameButton.buttonPressed.connect(toggleNewGame);
        recordsButton.buttonPressed.connect(toggleRecords);
        aboutButton.buttonPressed.connect(toggleAbout);
        newGameScreen.leave.connect(toggleMainMenu);
    }
}
