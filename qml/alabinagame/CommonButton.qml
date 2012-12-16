// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: button
    property string buttonText
    signal buttonPressed
    property bool animateShow: true
    NumberAnimation on scale {
        id: animateScale
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
            NumberAnimation {
                properties: "scale"
                duration: 500
            }
        }
    ]
    MouseArea {
        id: mouseRegion
        anchors.fill: parent
        onClicked: buttonPressed()
    }
    onAnimateShowChanged: {
        if (animateShow) {
            animateScale.start();
        } else {
            animateScale.complete();
        }
    }
}
