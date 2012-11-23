// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    signal donePressed
    signal restartPressed
    property string selector: "completed"
    Rectangle {
        anchors.fill: parent
        opacity: 0.8
        color: "gray"
    }
    GameLevelCompleted {
        id: completedScreen
        menuItemName: "completed"
        menuSelectorName: selector
        anchors.fill: parent
        opacityLimit: 1
        onRestartPressed: restartPressed()
    }
    ActiveScreen {
        id: finishScreen
        menuItemName: "finish"
        menuSelectorName: selector
        anchors.fill: parent
        opacityLimit: 1
        ListView {
            id: resultsList
            anchors.left: parent.left
            anchors.leftMargin: 100
            anchors.right: sideMenu.left
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: spacing
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            spacing: 100
            model: cSessionModel
            header: Item {
                width: resultsList.width
                height: resultsList.spacing + 50
                Item {
                    width: resultsList.width
                    height: 50
                    ButtonText {
                        anchors.right: parent.horizontalCenter
                        anchors.rightMargin: 100
                        text: cSessionModel.username + qsTr(", ваш результат: ")
                    }
                    ButtonText {
                        anchors.left: parent.horizontalCenter
                        anchors.leftMargin: 100
                        text: cSessionModel.totalPoints
                    }
                }
            }
            delegate: Item {
                width: resultsList.width
                height: 50
                ButtonText {
                    anchors.right: parent.horizontalCenter
                    anchors.rightMargin: 100
                    text: resultLevelName
                }
                ButtonText {
                    anchors.left: parent.horizontalCenter
                    anchors.leftMargin: 100
                    text: resultTotalPoints
                }
            }
        }
        Item {
            id: sideMenu
            anchors.right: parent.right
            width: 300
            height: parent.height
            StartButton {
                buttonText: "Главное меню"
                width: 200
                height: 50
                onButtonPressed: donePressed()
                anchors.centerIn: parent
            }
        }
    }
    ActiveScreen {
        id: recordsScreen
        menuItemName: "records"
        menuSelectorName: selector
        anchors.fill: parent
        opacityLimit: 1
        Records {
            anchors.centerIn: parent
        }
    }
    function toggleFinishScreen ()
    {
        selector = "finish";
    }

    Component.onCompleted: {
        completedScreen.continuePressed.connect(toggleFinishScreen);
        completedScreen.menuPressed.connect(toggleFinishScreen);
    }
}
