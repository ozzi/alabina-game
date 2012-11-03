// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    property string descriptionText

    Flickable {
        id: contentFlickable
        clip: true
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        contentWidth: contentDescription.width
        contentHeight: contentDescription.height
        boundsBehavior: Flickable.StopAtBounds
        interactive: false
        Text {
            id: contentDescription
            width: parent.width
            text: descriptionText
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignJustify
            wrapMode: Text.WordWrap
            font.pointSize: 20
            textFormat: Text.RichText
        }
    }
}
