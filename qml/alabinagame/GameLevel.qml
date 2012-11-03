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

    Item {
        property string selector: cSceneManager.state
        id: centralItem
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width * 0.6

        GameLevelChapterDescription {
            descriptionText: cDescriptionModel.description
            anchors.fill: parent
            menuItemName: "description"
            menuSelectorName: centralItem.selector
            opacityLimit: 0.8
        }

        GameLevelChapterTest {
            anchors.fill: parent
            menuItemName: "test"
            menuSelectorName: centralItem.selector
            opacityLimit: 0.8
        }
    }

    Item {
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: centralItem.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        GameImage/*Rectangle*/ {
            id: chapterImage
            width: parent.width
            height: width
            imagePath: cDescriptionModel.imagePath
            onButtonPressed: {}
        }

        Column {
            anchors.top: chapterImage.bottom
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            width: parent.width
            spacing: 30
            StartButton {
                width: parent.width/2
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: "Далее"
                onButtonPressed: cSceneManager.nextScene()
            }
            StartButton {
                width: parent.width/2
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: "Назад"
                onButtonPressed: cSceneManager.prevScene()
            }
            StartButton {
                width: parent.width/2
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: "Меню"
                onButtonPressed: gameWindow.menuSelector = "menu"
            }
        }
    }

    onGameLevelNameChanged: {
        cSceneManager.reset()
    }
}
