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
        property string selector: cSceneManager.state
        id: centralItem
        anchors.fill : parent
        GameLevelChapterDescription {
            descriptionText: cDescriptionModel.description
            anchors.fill: parent
            menuItemName: "description"
            menuSelectorName: centralItem.selector
            opacityLimit: 0.8
            onImagePressed: centralItem.selector = "gallery"
            onNextPressed: cSceneManager.nextScene()
            onPrevPressed: cSceneManager.prevScene()
        }

        GameLevelChapterTest {
            anchors.fill: parent
            menuItemName: "test"
            menuSelectorName: centralItem.selector
            opacityLimit: 0.8
        }

        GameLevelGallery {
            anchors.fill: parent
            menuItemName: "gallery"
            menuSelectorName: centralItem.selector
            opacityLimit: 0.8
        }
    }

    onGameLevelNameChanged: {
        cSceneManager.reset()
    }
}
