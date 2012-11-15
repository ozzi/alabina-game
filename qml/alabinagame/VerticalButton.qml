// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

CommonButton {
    radius: 10
    opacity: 0.7
    Text {
        text: buttonText
        anchors.centerIn: parent
        font.pointSize: 12
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        height: parent.height/4*3
        width: parent.width/4*3
        transform: Rotation {
            angle: 90
        }
    }
}
