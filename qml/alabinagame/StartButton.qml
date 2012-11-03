// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: button
    property string buttonText
    signal buttonPressed
    radius: 20
    opacity: 0.7
    Text {
        text: buttonText
        anchors.centerIn: parent
        font.pointSize: 18
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        height: parent.height/4*3
        width: parent.width/4*3
    }
    NumberAnimation on scale {
        from: 0; to: 1; duration: 1000
    }
    states: [
        State {
            name: "selected"
            when: mouseRegion.pressed == true
            PropertyChanges {
                target: button
                scale: 1.5
            }
        },
        State {
            name: "notselected"
            when: mouseRegion.pressed == false
            PropertyChanges {
                target: button
                scale: 1
            }
        }
    ]
    transitions: [
        Transition {
            from: "selected"
            to: "notselected"
            ParallelAnimation {
                NumberAnimation {
                    properties: "scale"
                    duration: 500
                }
            }
        }
    ]
    MouseArea {
        id: mouseRegion
        anchors.fill: parent
        onClicked: buttonPressed()
    }
}
