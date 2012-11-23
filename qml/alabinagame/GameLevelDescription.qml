// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    property string descriptionText
    property string descriptionImage
    signal imagePressed
    signal nextPressed
    signal prevPressed

    Flickable {
        id: contentFlickable
        clip: true
        interactive: false
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 38
        width: parent.width * 0.6
        contentWidth: contentFlickable.width
        contentHeight: contentDescription.height
        boundsBehavior: Flickable.StopAtBounds
        GameText {
            id: contentDescription
            width: parent.width
            text: descriptionText
        }
        function prevPage ()
        {
            contentY -= height;
        }
        function nextPage ()
        {
            contentY += height;
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
            source: descriptionImage
            onButtonPressed: imagePressed()
        }

        Column {
            id: chapterMenu
            anchors.top: chapterImage.bottom
            anchors.topMargin: 20
            width: parent.width
            height: (parent.height - chapterImage.height)/2
            spacing: 30
            StartButton {
                width: parent.width/2
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: "Фотоматериалы"
                onButtonPressed: imagePressed()
            }
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
        Item {
            anchors.top: chapterMenu.bottom
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            width: parent.width
            StartButton {
                id: upButton
                width: parent.width/2
                height: 50
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: "Предыдущая страница"
                opacity: { return contentFlickable.contentY > 0 ? 0.8 : 0; }
            }
            StartButton {
                id: bottomButton
                width: parent.width/2
                height: 50
                anchors.top: upButton.bottom
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: "Следующая страница"
                opacity: { return contentFlickable.contentY + contentFlickable.height < contentFlickable.contentHeight ? 0.8 : 0; }
            }
        }
    }
    Component.onCompleted: {
        upButton.buttonPressed.connect(contentFlickable.prevPage);
        bottomButton.buttonPressed.connect(contentFlickable.nextPage);
    }
}
