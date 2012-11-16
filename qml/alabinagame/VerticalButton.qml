// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

CommonButton {
    radius: 10
    opacity: 0.7
    Text {
        text: buttonText
        anchors.centerIn: parent
        font.pointSize: 12
        rotation: 270
    }
}
