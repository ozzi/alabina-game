// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    property string gameLevelName
    property string gameLevelDescription
    property string gameLevelImage

    /*Image {
        source: gameLevelImage
        fillMode: Image.Stretch
        anchors.fill: parent
    }*/
    /*StartButton {
        width: parent.width/2
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        buttonText: "Меню"
        onButtonPressed: gameWindow.menuSelector = "menu"
    }*/
    Item {
        id: centralItem
        property string selector: cSceneManager.state
        anchors.fill : parent
        GameLevelDescription {
            menuItemName: "description"
            menuSelectorName: centralItem.selector
            descriptionText: cDescriptionModel.description
            descriptionImage: cDescriptionModel.imagePath
            anchors.fill: parent
            opacityLimit: 0.8
            onImagePressed: centralItem.selector = "gallery"
            onNextPressed: cSceneManager.nextScene()
            onPrevPressed: cSceneManager.prevScene()
        }
        GameLevelGallery {
            menuItemName: "gallery"
            menuSelectorName: centralItem.selector
            anchors.fill: parent
            opacityLimit: 0.8
            onExitButtonTapped: centralItem.selector = "description"
        }
        GameLevelTest {
            menuItemName: "test"
            menuSelectorName: centralItem.selector
            anchors.fill: parent
            opacityLimit: 0.8
        }
        GameLevelFinal {
            menuItemName: "final"
            menuSelectorName: centralItem.selector
            anchors.fill: parent
            opacityLimit: 0.8
        }
    }
    onGameLevelNameChanged: {
        cSceneManager.reset()
    }
}
