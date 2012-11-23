// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ActiveScreen {
    signal continuePressed
    signal restartPressed
    signal menuPressed
    signal highlightPressed
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
        model: cResultModel
        header: Item {
            width: resultsList.width
            height: resultsList.spacing + 50
            Item {
                width: resultsList.width
                height: 50
                anchors.left: parent.left
                anchors.right: parent.right
                ButtonText {
                    text: qsTr("Всего набрано баллов: ") + cResultModel.pointsTotal
                }
            }
        }
        delegate: Item {
            width: resultsList.width
            height: 50
            ButtonText {
                text: {
                    var result = resultPoints;
                    switch (resultPoints) {
                    case 1:
                        result += " ответ"
                        break;
                    case 2:
                    case 3:
                    case 4:
                        result += " ответа"
                        break;
                    default:
                        result += " ответов";
                        break;
                    }

                    switch (index) {
                    case 0:
                        result += " без ошибок";
                        break;
                    case 1:
                        result += " с одной ошибкой";
                        break;
                    case 2:
                        result += " с двумя ошибками";
                        break;
                    default:
                        result += " с тремя и более ошибками";
                        break;
                    }
                    return result;
                }
            }
        }
    }

    Column {
        id: sideMenu
        width: 200
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.right: parent.right
        anchors.rightMargin: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        spacing: 100
        StartButton {
            width: parent.width
            height: 50
            buttonText: "Продолжить"
            onButtonPressed: continuePressed()
        }
        StartButton {
            width: parent.width
            height: 50
            buttonText: "Заново"
            onButtonPressed: restartPressed()
        }
        StartButton {
            width: parent.width
            height: 50
            buttonText: "Вернуться в меню"
            onButtonPressed: menuPressed()
        }
    }
}
