// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    id: listScreen
    signal backButtonPressed
    ListView {
        id: galleryListView
        property string imageState: "partscreen"
        anchors.fill: parent
        model: cDescriptionModel
        delegate: Item {
            id: imageItem
            property variant myData: model
            state: galleryListView.imageState
            width: galleryListView.width
            height: galleryListView.height
            GameImage {
                id: imageFS
                source: imagePath
                width: parent.width*2/3
                height: parent.height
                anchors.left: parent.left
                anchors.top: parent.top
            }
            GameText {
                text: imageDescription
                anchors.left: imageFS.right
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.topMargin: sideMenu.height + 40
            }
            states: [
                State {
                    name: "fullscreen"
                    PropertyChanges {
                        target: imageFS
                        width: imageItem.width
                    }
                },
                State {
                    name: "partscreen"
                    PropertyChanges {
                        target: imageFS
                        width: imageItem.width*2/3
                    }
                }
            ]
            transitions: [
                Transition {
                    from: "fullscreen"
                    to: "partscreen"
                    reversible: true
                    NumberAnimation {
                        target: imageFS;
                        property: "width";
                        duration: 300;
                        easing.type: Easing.InOutQuad
                    }
                }
            ]
        }
        onCurrentIndexChanged: {
            if (!currentItem.myData.imageDescription.length) {
                imageState = "fullscreen";
            }
        }

        function fastSetIndex (index) {
            var old_speed = highlightMoveSpeed
            highlightMoveSpeed = -1
            currentIndex = index
            highlightMoveSpeed = old_speed
        }
        function toggleFS()
        {
            if (imageState == "fullscreen") {
                imageState = "partscreen";
            } else {
                imageState = "fullscreen"
            }
        }
    }
    Column {
        id: sideMenu
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
            buttonText: qsTr("Галерея")
        }
        StartButton {
            id: fsButton
            width: parent.width
            height: 50
            buttonText: qsTr("Вид")
            onButtonPressed: galleryListView.toggleFS()
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
