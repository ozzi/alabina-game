// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    signal startButtonPressed
    signal leaveButtonPressed
    ButtonText {
        id: titleText
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        text: cPreviewModel.currentLevelName
    }
    ListView {
        id: levelImage
        anchors.top: titleText.bottom
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        height: 400
        spacing: 20
        interactive: false
        clip: true
        orientation: ListView.Horizontal
        delegate: GameImage {
            width: height
            height: levelImage.height
            source: display
        }
        model: cPreviewModel
    }
    GameText {
        id: descriptionText
        anchors.top: levelImage.bottom
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: sideMenu.left
        anchors.rightMargin: 50
        height: 100
        text: cPreviewModel.currentLevelDescription
    }
    Column {
        id: sideMenu
        width: 270
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: levelImage.bottom
        anchors.topMargin: 50
        anchors.bottom: parent.bottom
        spacing: 50
        StartButton {
            width: parent.width
            height: 50
            buttonText: "Начать"
            onButtonPressed: startButtonPressed()
        }
        StartButton {
            width: parent.width
            height: 50
            buttonText: "Вернуться в меню"
            onButtonPressed: leaveButtonPressed()
        }
    }
}
