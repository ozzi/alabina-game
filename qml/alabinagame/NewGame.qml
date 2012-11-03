// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: gameWindow
    property string menuSelector: "menu"
    ActiveScreen {
        id: levelMenu
        anchors.fill: parent
        menuItemName: "menu"
        menuSelectorName: gameWindow.menuSelector
        Component {
            id: levelTitleDelegate
            StartButton {
                width: 400
                height: 100
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: levelName
                onButtonPressed: {
                    gameWindow.menuSelector = "gameLevel";
                    levelScreen.levelName = levelName;
                    levelScreen.levelDescription = levelDescription;
                    levelScreen.levelImage = levelImage;
                    cLevelModel.setLevel(index);
                }
            }
        }
        ListView {
            id: levelTitles
            width: parent.width
            height: parent.height/3*2
            anchors.verticalCenter: parent.verticalCenter
            spacing: 30
            delegate: levelTitleDelegate
            model: cLevelModel
            footer: Item {
                anchors.horizontalCenter: parent.horizontalCenter
                width: backToMainMenuButton.width
                height: backToMainMenuButton.height + levelTitles.spacing
                StartButton {
                    id: backToMainMenuButton
                    width: 400
                    height: 100
                    anchors.bottom: parent.bottom
                    buttonText: qsTr("Главное меню")
                    onButtonPressed: mainWindow.menuSelector = "mainMenu"
                }
            }
        }
    }
    ActiveScreen {
        id: levelScreen
        property string levelName
        property string levelDescription
        property string levelImage
        anchors.fill: parent
        menuItemName: "gameLevel"
        menuSelectorName: gameWindow.menuSelector
        GameLevel {
            gameLevelName: levelScreen.levelName
            gameLevelDescription: levelScreen.levelDescription
            gameLevelImage: levelScreen.levelImage
            anchors.fill: parent
        }
    }
}
