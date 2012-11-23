// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    property string gallerySelector: "grid"
    signal exitButtonTapped
    GalleryGridScreen {
        id: gridScreen
        menuItemName: "grid"
        menuSelectorName: gallerySelector
        width: parent.width
        anchors.fill: parent
    }

    GalleryListScreen {
        id: listScreen
        menuItemName: "list"
        menuSelectorName: gallerySelector
        anchors.fill: parent
    }
    Component.onCompleted: {
        gridScreen.galleryImagePressed.connect(showListScreen)
        gridScreen.backButtonPressed.connect(exitButtonTapped)
        listScreen.backButtonPressed.connect(showGridScreen)
    }
    function showListScreen (index) {
        gallerySelector = "list"
        listScreen.showImageAtIndex(index)
    }
    function showGridScreen () {
        gallerySelector = "grid"
    }
}
