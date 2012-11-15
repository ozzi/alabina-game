// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Image {
    id: gameImage
    signal buttonPressed
    fillMode: Image.PreserveAspectFit
    asynchronous: true
    cache: false
    smooth: true
    sourceSize.width: 1280
    sourceSize.height: 1024
    MouseArea {
        anchors.fill: parent
        onClicked: buttonPressed()
    }
}
