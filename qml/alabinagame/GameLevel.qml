// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    id: levelScreen
    signal leave
    signal nextLevel
    property string selector
    property string menuImage
    MenuBackground {
        source: menuImage
    }
    Rectangle {
        anchors.fill: parent
        opacity: 0.8
        color: "gray"
    }
    GameLevelInitial {
        menuItemName: "initial"
        menuSelectorName: selector
        anchors.fill: parent
        opacityLimit: 1
        onStartButtonPressed: cSceneManager.nextScene()
        onLeaveButtonPressed: leave()
    }
    GameLevelDescription {
        menuItemName: "description"
        menuSelectorName: selector
        descriptionTitle: cSceneManager.chapter
        descriptionText: cDescriptionModel.description
        descriptionImage: cDescriptionModel.imagePath
        anchors.fill: parent
        opacityLimit: 1
        onImagePressed: selector = "gallery"
        onNextPressed: cSceneManager.nextScene()
        onPrevPressed: cSceneManager.prevScene()
    }
    GameLevelGallery {
        menuItemName: "gallery"
        menuSelectorName: selector
        anchors.fill: parent
        opacityLimit: 1
        onExitButtonTapped: selector = "description"
    }
    GameLevelTest {
        menuItemName: "test"
        menuSelectorName: selector
        anchors.fill: parent
        opacityLimit: 1
    }
    GameLevelCompleted {
        menuItemName: "final"
        menuSelectorName: selector
        anchors.fill: parent
        opacityLimit: 1
        onContinuePressed: nextLevel()
        onRestartPressed: cSceneManager.reset()
        onMenuPressed: leave()
    }
    function toggleState()
    {
        selector = cSceneManager.state;
    }

    Component.onCompleted: {
        toggleState();
        cSceneManager.stateChanged.connect(toggleState);
    }
}
