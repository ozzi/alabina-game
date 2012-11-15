// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    property string descriptionText
    signal imagePressed
    signal nextPressed
    signal prevPressed

    Flickable {
        id: contentFlickable
        clip: true
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: parent.width * 0.6
        contentWidth: contentFlickable.width
        contentHeight: contentDescription.height
        boundsBehavior: Flickable.StopAtBounds
        interactive: false
        GameText {
            id: contentDescription
            width: parent.width
            text: descriptionText
        }
    }
    Item {
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: contentFlickable.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        GameImage {
            id: chapterImage
            width: parent.width
            height: width
            source: cDescriptionModel.imagePath
            onButtonPressed: imagePressed()
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
                onButtonPressed: nextPressed()
            }
            StartButton {
                width: parent.width/2
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: "Назад"
                onButtonPressed: prevPressed()
            }
        }
    }
}
