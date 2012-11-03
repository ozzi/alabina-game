// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: activeScreen
    property string menuItemName
    property variant menuSelectorName
    property double opacityLimit: 1
    states: [
        State {
            name: "show"
            when: menuSelectorName == menuItemName
            PropertyChanges {
                target: activeScreen
                opacity: opacityLimit
            }
        },
        State {
            name: "hide"
            when: menuSelectorName != menuItemName
            PropertyChanges {
                target: activeScreen
                opacity: 0
            }
        }
    ]
    transitions: [
        Transition {
            from: "hide"
            to: "show"
            NumberAnimation {
                properties: "opacity"
                duration: 1500
            }
        },
        Transition {
            from: "show"
            to: "hide"
            NumberAnimation {
                properties: "opacity"
                duration: 500
            }
        }
    ]
}
