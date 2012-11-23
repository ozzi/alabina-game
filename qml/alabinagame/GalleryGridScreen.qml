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
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: sideMenu.left
        anchors.rightMargin: 20
        cellWidth: width/4
        cellHeight: height/3
        clip: true
        interactive: false
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
        function reset ()
        {
            contentY = 0;
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
        id: sideMenu
        anchors.right: parent.right
        width: 60
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        VerticalButton  {
            id: gridBackButton
            anchors.top: sideMenu.top
            anchors.topMargin: 100
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 20
            height: 100
            buttonText: "Описание"
        }
        VerticalButton {
            id: gridPrevButton
            anchors.top: gridBackButton.bottom
            anchors.topMargin: 100
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 20
            height: 100
            buttonText: "Назад"
            opacity: { return galleryGridView.contentY > 0 ? 0.8 : 0; }
        }
        VerticalButton {
            id: gridNextButton
            anchors.bottom: sideMenu.bottom
            anchors.bottomMargin: 100
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 20
            height: 100
            buttonText: "Далее"
            opacity: { return galleryGridView.contentY + galleryGridView.height < galleryGridView.contentHeight ? 0.8 : 0; }
        }
    }

    Component.onCompleted: {
        console.debug("galleryGridView height " + galleryGridView.height);
        console.debug("galleryGridView cellHeight " + galleryGridView.cellHeight);
        gridPrevButton.buttonPressed.connect(galleryGridView.prevPage);
        gridNextButton.buttonPressed.connect(galleryGridView.nextPage);
        gridBackButton.buttonPressed.connect(backButtonPressed);
        backButtonPressed.connect(galleryGridView.reset);
    }
}
