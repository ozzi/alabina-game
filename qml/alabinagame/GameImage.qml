// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Image {
    id: gameImage
    property string imagePath: "http://qt.nokia.com/logo.png"
    signal buttonPressed
    source: imagePath
    fillMode: Image.PreserveAspectFit
    MouseArea {
        anchors.fill: parent
        onClicked: buttonPressed()
    }
}
