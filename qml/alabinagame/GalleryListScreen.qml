// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    id: listScreen
    signal backButtonPressed
    ListView {
        id: galleryListView
        anchors.fill: parent
        model: cDescriptionModel
        delegate: Column {
            GameImage {
                id: imageFS
                source: imagePath
                width: galleryListView.width
                height: galleryListView.height/10*9
            }
            GalleryPreviewText {
                text: imageDescription
                width: imageFS.width
                height: galleryListView.height - imageFS.height
            }

        }
        function fastSetIndex (index) {
            var old_speed = highlightMoveSpeed
            highlightMoveSpeed = -1
            currentIndex = index
            highlightMoveSpeed = old_speed
        }
    }
    Column {
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: 200
        spacing: 20
        StartButton {
            id: listBackButton
            width: parent.width
            height: 50
            buttonText: qsTr("Галлерея")
        }
        StartButton {
            id: listNextButton
            width: parent.width
            height: 50
            buttonText: qsTr("Далее")
            opacity: { return galleryListView.currentIndex + 1 == galleryListView.count ? 0 : 0.8 }
        }
        StartButton {
            id: listPrevButton
            width: parent.width
            height: 50
            buttonText: qsTr("Назад")
            opacity: { return galleryListView.currentIndex == 0 ? 0 : 0.8 }
        }
    }
    function showImageAtIndex (index) {
        galleryListView.fastSetIndex(index)
    }

    Component.onCompleted: {
        listNextButton.buttonPressed.connect(galleryListView.incrementCurrentIndex)
        listPrevButton.buttonPressed.connect(galleryListView.decrementCurrentIndex)
        listBackButton.buttonPressed.connect(backButtonPressed)
    }
}
