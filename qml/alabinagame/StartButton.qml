// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

CommonButton {
    radius: 20
    opacity: 0.7
    ButtonText {
        text: buttonText
        anchors.centerIn: parent
        height: parent.height/4*3
        width: parent.width/4*3
    }
}
