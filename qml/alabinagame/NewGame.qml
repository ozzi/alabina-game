// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    id: gameWindow
    signal leave
    signal enter
    property string menuSelector: "menu"
    ActiveScreen {
        id: levelMenu
        signal mainMenuPressed
        signal gameLevelPressed(variant level)
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
                    levelMenu.gameLevelPressed(index);
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
                    onButtonPressed: levelMenu.mainMenuPressed()
                }
            }
        }
    }
    GameLevel {
        id: levelScreen
        anchors.fill: parent
        menuItemName: "gameLevel"
        menuSelectorName: gameWindow.menuSelector
    }
    FinishGame {
        id: finishGame
        anchors.fill: parent
        menuItemName: "finishGame"
        menuSelectorName: gameWindow.menuSelector
    }

    function toggleSelectedLevel (level)
    {
        cLevelModel.level = level;
        menuSelector = "gameLevel";
        switch (level) {
        case 0:
            levelScreen.menuImage = "qrc:/money.jpg";
            break;
        case 1:
            levelScreen.menuImage = "qrc:/weapon.jpg";
            break;
        case 2:
            levelScreen.menuImage = "qrc:/plakaty.jpg";
            break;
        default:
            levelScreen.menuImage = "qrc:/main.jpg";
            break;
        }
    }
    function toggleLevelList ()
    {
        menuSelector = "menu";
    }
    function toggleNextLevel ()
    {
        ++cLevelModel.level;
    }
    function toggleFinishGame ()
    {
        menuSelector = "finishGame";
    }

    Component.onCompleted: {
        levelMenu.mainMenuPressed.connect(leave);
        levelMenu.gameLevelPressed.connect(toggleSelectedLevel);
        levelScreen.leave.connect(toggleLevelList);
        levelScreen.nextLevel.connect(toggleNextLevel);
        cSessionModel.allLevelsCompleted.connect(toggleFinishGame);
        finishGame.donePressed.connect(leave);
        enter.connect(toggleLevelList);
    }
}
