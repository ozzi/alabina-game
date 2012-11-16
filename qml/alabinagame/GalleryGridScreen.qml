// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    id: gridScreen
    signal galleryImagePressed (int index)
    signal backButtonPressed
    GridView {
        id: galleryGridView
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: sideMenu.left
        anchors.rightMargin: 20
        cellWidth: width/4
        cellHeight: height/3
        model: cDescriptionModel
        delegate: Column {
            id: imageContent
            GameImage {
                id: imagePreview
                source: imagePath
                width: galleryGridView.cellWidth - 10
                height: galleryGridView.cellHeight/3*2
            }
            GalleryPreviewText {
                text: imageDescription
                width: imagePreview.width
                height: galleryGridView.cellHeight - imagePreview.height - 10
            }
            Component.onCompleted: {
                imagePreview.buttonPressed.connect(function() {gridScreen.galleryImagePressed(index)})
            }
        }
        function prevPage ()
        {
            contentY -= height;
        }
        function nextPage ()
        {
            galleryGridView.contentY += galleryGridView.height;
        }
    }
    Item {
        id: sideMenu
        anchors.right: parent.right
        width: 40
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        VerticalButton  {
            id: gridBackButton
            anchors.top: sideMenu.top
            anchors.topMargin: 100
            width: sideMenu.width
            height: 100
            buttonText: "description"
        }
        VerticalButton {
            id: gridPrevButton
            anchors.top: gridBackButton.top
            anchors.topMargin: 100
            width: sideMenu.width
            height: 100
            buttonText: "prev"
            opacity: { return galleryGridView.contentY > 0 ? 1 : 0; }
        }
        VerticalButton {
            id: gridNextButton
            anchors.bottom: sideMenu.bottom
            anchors.bottomMargin: 100
            width: sideMenu.width
            height: 100
            buttonText: "next"
            opacity: { return galleryGridView.contentY + galleryGridView.height < galleryGridView.contentHeight ? 1 : 0; }
        }
    }
    Component.onCompleted: {
        gridPrevButton.buttonPressed.connect(galleryGridView.prevPage)
        gridNextButton.buttonPressed.connect(galleryGridView.nextPage)
        gridBackButton.buttonPressed.connect(backButtonPressed)
    }
}
