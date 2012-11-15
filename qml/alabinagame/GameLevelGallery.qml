// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    property string gallerySelector: "grid"
    ActiveScreen {
        menuItemName: "grid"
        menuSelectorName: gallerySelector
        anchors.fill: parent
        GridView {
            id: galleryGridView
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: sideMenu.left
            cellWidth: galleryGridView.width/6
            cellHeight: galleryGridView.height/5
            model: cDescriptionModel
            delegate: Column {
                GameImage {
                    id: imagePreview
                    source: imagePath
                    width: galleryGridView.cellWidth - 10
                    height: galleryGridView.cellHeight/3*2
                    onButtonPressed: {
                        console.debug("cell_w " + galleryGridView.cellWidth + " cell_h " + galleryGridView.cellHeight);
                        console.debug("galleryGridView wid " + galleryGridView.width + " hei " + galleryGridView.height);
                        console.debug("parent width " + galleryGridView.parent.width);
                        console.debug("this.width " + width + " this.height " + height);
                        gallerySelector = "list"
                        var old_speed = galleryListView.highlightMoveSpeed
                        galleryListView.highlightMoveSpeed = -1
                        galleryListView.currentIndex = index
                        galleryListView.highlightMoveSpeed = old_speed
                    }
                }
                GalleryPreviewText {
                    text: imageDescription
                    width: imagePreview.width
                    height: galleryGridView.cellHeight - imagePreview.height - 10
                }
            }
        }
        Column {
            id: sideMenu
            anchors.right: parent.right
            width: 40
            anchors.top: parent.top
            anchors.topMargin: 100
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            spacing: 30
            StartButton {
                width: sideMenu.width
                height: 100
                buttonText: "next"
                onButtonPressed: {
                    ;
                }
            }
            StartButton {
                width: sideMenu.width
                height: 100
                buttonText: "prev"
            }
            StartButton  {
                width: sideMenu.width
                height: 100
                buttonText: "back"
            }
        }
    }
    ActiveScreen {
        menuItemName: "list"
        menuSelectorName: gallerySelector
        anchors.fill: parent
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
        }
        Column {
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: 100
            spacing: 20
            StartButton {
                width: parent.width
                height: 50
                buttonText: qsTr("Gallery")
                onButtonPressed: gallerySelector = "grid"
            }
            StartButton {
                width: parent.width
                height: 50
                buttonText: qsTr("Next")
                onButtonPressed: galleryListView.incrementCurrentIndex()
            }
            StartButton {
                width: parent.width
                height: 50
                buttonText: qsTr("Prev")
                onButtonPressed: galleryListView.decrementCurrentIndex()
            }
        }
    }
}
